//#include <stdint.h>

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//#include <cstdio>
//#include <cstdlib>
//#include <vector>
//#include <string>

#include "types.h"
#include "token.h"

#include "elf.h"

extern "C" const Token* GetToken();
extern "C" int SetScanBuffer(char *base, int size);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline word ReverseWord(word v) { return ((v&0x00FF)<<8 | (v&0xFF00)>>8); }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline dword ReverseDword(dword v) 
{ 
	v = (v&0x00FF00FF)<<8 | (v&0xFF00FF00)>>8;
	return (v&0x0000FFFF)<<16 | (v&0xFFFF0000)>>16;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void ReverseFileHeader(Elf32_Ehdr *h)
{
    h->e_type		= ReverseWord	(h->e_type		);		
    h->e_machine	= ReverseWord	(h->e_machine	);
    h->e_version	= ReverseDword	(h->e_version	);
    h->e_entry		= ReverseDword	(h->e_entry		);
    h->e_phoff		= ReverseDword	(h->e_phoff		);	
    h->e_shoff		= ReverseDword	(h->e_shoff		);
    h->e_flags		= ReverseDword	(h->e_flags		);
    h->e_ehsize		= ReverseWord	(h->e_ehsize	);
    h->e_phentsize	= ReverseWord	(h->e_phentsize	);	
    h->e_phnum		= ReverseWord	(h->e_phnum		);
    h->e_shentsize	= ReverseWord	(h->e_shentsize	);
    h->e_shnum		= ReverseWord	(h->e_shnum		);
    h->e_shstrndx	= ReverseWord	(h->e_shstrndx	);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//using namespace std;
//
//struct Patch
//{
//  u32 address;
//  vector<byte> values;
//};
//
//vector<Patch> entries;


static const char *tokenStr = 0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void printUsage()
{
  printf("Usage: ElfPatch filename filename.elf\n");
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static u32			adr = 0;
static u32			fileSize = 0;
static FILE*		srcfile = 0;
static byte			srcbuf[1024];
static u32			srcfileSize = 0;
static FILE* 		dstfile = 0;
static FILE* 		elfFile = 0;
static u32			elfSize = 0;
static const byte*	elfData = 0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static bool OpenDstFile(const char *filename)
{
	dstfile = fopen(filename, "r+b");

	if (!dstfile)
	{
		printf("Unable to open file %s. Exiting.\n", filename);
		return false;
	};

	fseek(dstfile, 0L, SEEK_END);
	fileSize = ftell(dstfile);

	return true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static bool OpenELF(const char *filename)
{
	elfFile = fopen(filename, "rb");

	if (!elfFile)
	{
		printf("Unable to open ELF file %s. Exiting.\n", filename);
		return false;
	};

	fseek(elfFile, 0L, SEEK_END);
	elfSize = ftell(elfFile);

	elfData = (const byte*)malloc(elfSize);

	if (elfData == 0)
	{
		printf("Unable to allocate memory for ELF file. Exiting.\n");
		return false;
	};

	fseek(elfFile, 0, SEEK_SET);
	u32 t = fread((void*)elfData, 1, elfSize, elfFile);

	if (t != elfSize)
	{
		printf("Error reading ELF file. Exiting.\n");
		
		return false;
	};

	Elf32_Ehdr *hdr = (Elf32_Ehdr*)elfData;

	if (hdr->e_ident[EI_MAG0] != ELFMAG0 || hdr->e_ident[EI_MAG1] != ELFMAG1 || hdr->e_ident[EI_MAG2] != ELFMAG2 || hdr->e_ident[EI_MAG3] != ELFMAG3)
	{
		return false;
	};

	if (hdr->e_ident[EI_CLASS] != ELFCLASS32 && hdr->e_ident[EI_CLASS] != ELFCLASS64)
	{
		return false;
	};

	printf("Class:      %s\n", class_table[hdr->e_ident[EI_CLASS] - ELFCLASS32].str);

	if (hdr->e_ident[EI_DATA] > ELFDATA2MSB)
	{
		return false;
	};

	printf("Encoding:   %s\n", endian_table[hdr->e_ident[EI_DATA]].str);

	if (hdr->e_ident[EI_DATA] == ELFDATA2MSB)
	{
		ReverseFileHeader(hdr);
	};

	if (hdr->e_ident[EI_VERSION] > EV_CURRENT)
	{
		return false;
	};

	printf("ELFVersion: %s\n", version_table[hdr->e_ident[EI_VERSION]].str);
	
	if (hdr->e_type > ET_CORE)
	{
		return false;
	};

	printf("Type:       %s\n", type_table[hdr->e_type].str);


	if (hdr->e_machine > EM_BPF)
	{
		return false;
	};

	printf("Machine:    %s\n", machine_table[hdr->e_machine].str);
	


	return true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc, const char* argv[])
{
	if (argc < 3)
	{
		printUsage();
		return 1;
	}

	static const Token *token;

	tokenStr = GetCommandLineA();

	int len = strlen(tokenStr) + 2;

	char *buf = (char*)malloc(len);

	if (buf == 0)
	{
		printf("Unable to allocate memory. Exiting.\n");
		return 1;
	};

	strcpy(buf, tokenStr);

	buf[len-1] = 0; buf[len-2] = 0;

	if (SetScanBuffer(buf, len) == 0)
	{
		printf("Unable to set Flex scanner input buffer. Exiting.\n");
		return 1;
	};
	
	token = GetToken();

	token = GetToken();

	if (token->id != FILENAME && token->id != STR)
	{
		printf("Bad file name %s. Exiting.\n", token->str);
		return 1;
	};

	if (!OpenDstFile(token->str))
	{
		return 1;
	}

	token = GetToken();

	if (token->id != FILENAME && token->id != STR)
	{
		printf("Bad ELF file name %s. Exiting.\n", token->str);
		return 1;
	};

	if (!OpenELF(token->str))
	{
		return 1;
	};

	u32 value;

	u32 t, t2, t3;

	byte state = 0;

	bool run = true;

	bool assign = true;

	while (run)
	{
		switch (state)
		{
			case 0: // num

				token = GetToken();

			case 1: 

				if (token->id == FILENAME || token->id == STR)
				{
					state = 4;

					break;
				}
				else if (token->id != NUM)
				{
					printf("Error processing number %s; patching failed\n", token->str);

					return 3;
				};

			case 2: 

				value = strtoul(token->str, 0, 0);

				token = GetToken();

				if (token->id == ASSIGN)
				{
					if (!assign)
					{
						printf("Error: assign not allowed here\n", token->str);
						return 3;
					}
					else if (value >= fileSize)
					{
						printf("Error: address too big; patching failed\n", token->str);
						return 3;
					}
					else
					{
						adr = value;

						assign = false;

						printf("\nPatch address 0x%X:\n", adr);

						//token = GetToken();

						//state = (token->id == FILENAME || token->id == STR) ? 4 : 1;

						state = 0;

						break;
					};
				};

			case 3: // write byte

				if (adr >= fileSize)
				{
					printf("Patch exceeds file size. Exiting.\n");
					return 3;
				};

				if (value > 0xFF)
				{
					printf("Patch value 0x%X exceeds 0xFF. Exiting.\n", value);
					return 3;
				};

				fseek(dstfile, adr++, SEEK_SET);
				t = fwrite(&value, 1, 1, dstfile);

				if (t != 1)
				{
					printf("Error writing file; patching failed\n", token->str);
					return 3;
				};

				printf("0x%02X ", value);

				assign = true;

//				token = GetToken();

				if (token->id == COMMA)
				{
					token = GetToken();
				};

				run = (token->id != 0);

				state = 1;

				break;

			case 4: //write dstfile

				srcfile = fopen(token->str, "rb");

				if (!srcfile)
				{
					printf("Unable to open file %s. Exiting.\n", token->str);
					return 3;
				};


				fseek(srcfile, 0L, SEEK_END);
				srcfileSize = ftell(srcfile);

				printf("File %s, size %u - ", token->str, srcfileSize);

				if (srcfileSize == 0)
				{
					printf("Warring: Patch size file %s is 0.\n", token->str);
				};

				if ((adr+srcfileSize) >= fileSize)
				{
					printf("Patch size file %s too big. Exiting.\n", token->str);
					return 3;
				};

				fseek(srcfile, 0, SEEK_SET);
				fseek(dstfile, adr, SEEK_SET);

				t3 = srcfileSize;

				while(t3 > 0)
				{
					t = fread(srcbuf, 1, sizeof(srcbuf), srcfile);

					t3 -= t;

					t2 = fwrite(srcbuf, 1, t, dstfile);

					if (t2 != t)
					{
						printf("Error writing file; patching failed\n", token->str);
						return 3;
					};

				};

				printf("writing %u bytes\n", srcfileSize);

				adr += srcfileSize;

				printf("Patch address 0x%X:\n", adr);

				assign = true;

				token = GetToken();

				if (token->id == COMMA)
				{
					token = GetToken();
				};

				run = (token->id != 0);

				state = 1;

				break;
		};
	};
  
  //for (vector<Patch>::const_iterator it = entries.begin(); it != entries.end(); ++it)
  //{
  //  const Patch& patch = *it;
  //  
  //  if (patch.address + patch.values.size() >= fileSize)
  //  {
  //    printf("Patch exceeds dstfile size. Exiting.\n");
  //    break;
  //  }
  //  
  //  fseek(dstfile, patch.address, SEEK_SET);
  //  fwrite(&patch.values[0], 1, patch.values.size(), dstfile);
  //}
  
  fclose(dstfile);

	printf("\nPatching done\n", token->str);

  return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
