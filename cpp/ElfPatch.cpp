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

static bool	bigEndian = false;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline word ReverseWord(word v) { return ((v&0x00FF)<<8 | (v&0xFF00)>>8); }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline dword ReverseDword(dword v) 
{ 
	v = (v&0x00FF00FF)<<8 | (v&0xFF00FF00)>>8;
	return (v&0x0000FFFF)<<16 | (v&0xFFFF0000)>>16;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void InitFileHeader(Elf32_Ehdr *h)
{
	if (bigEndian)
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
	};
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void InitSectionHeader(Elf32_Shdr *h)
{
	if (bigEndian)
	{
		h->sh_name		= ReverseDword	(h->sh_name			);		
		h->sh_type		= ReverseDword	(h->sh_type			);
		h->sh_flags		= ReverseDword	(h->sh_flags		);
		h->sh_addr		= ReverseDword	(h->sh_addr			);
		h->sh_offset	= ReverseDword	(h->sh_offset		);	
		h->sh_size		= ReverseDword	(h->sh_size			);
		h->sh_link		= ReverseDword	(h->sh_link			);
		h->sh_info		= ReverseDword	(h->sh_info			);
		h->sh_addralign	= ReverseDword	(h->sh_addralign	);	
		h->sh_entsize	= ReverseDword	(h->sh_entsize		);
	};
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
static Elf32_Ehdr	*ehdr = 0;
static Elf32_Shdr	*shdr = 0;

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

	ehdr = (Elf32_Ehdr*)elfData;

	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 || ehdr->e_ident[EI_MAG1] != ELFMAG1 || ehdr->e_ident[EI_MAG2] != ELFMAG2 || ehdr->e_ident[EI_MAG3] != ELFMAG3)
	{
		return false;
	};

	if (ehdr->e_ident[EI_CLASS] != ELFCLASS32 && ehdr->e_ident[EI_CLASS] != ELFCLASS64)
	{
		return false;
	};

	printf("Class:      %s\n", class_table[ehdr->e_ident[EI_CLASS] - ELFCLASS32].str);

	if (ehdr->e_ident[EI_DATA] > ELFDATA2MSB)
	{
		return false;
	};

	printf("Encoding:   %s\n", endian_table[ehdr->e_ident[EI_DATA]].str);

	bigEndian = (ehdr->e_ident[EI_DATA] == ELFDATA2MSB);

	InitFileHeader(ehdr);

	if (ehdr->e_ident[EI_VERSION] > EV_CURRENT)
	{
		return false;
	};

	printf("ELFVersion: %s\n", version_table[ehdr->e_ident[EI_VERSION]].str);
	
	if (ehdr->e_type > ET_CORE)
	{
		return false;
	};

	printf("Type:       %s\n", type_table[ehdr->e_type].str);


	if (ehdr->e_machine > EM_BPF)
	{
		return false;
	};

	printf("Machine:    %s\n", machine_table[ehdr->e_machine].str);
	

	shdr = (Elf32_Shdr*)(elfData+ehdr->e_shoff);

	if (shdr == 0 || ehdr->e_shnum == 0 || ehdr->e_shentsize < sizeof(Elf32_Shdr))
	{
		printf("ERROR: ELF file %s has no section header table. Exiting.\n", filename);

		return false;
	};


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

//	u32 value;

	u32 t;

	//byte state = 0;

	//bool run = true;

	//bool assign = true;

	u32 count = ehdr->e_shnum;

	byte *p = (byte*)shdr;

	while (count > 0)
	{
		InitSectionHeader(shdr);

		if (shdr->sh_type == SHT_PROGBITS)
		{
			printf("Patch section: address 0x%08lX; size 0x%08lX\n", shdr->sh_addr, shdr->sh_size);

			if ((shdr->sh_addr+shdr->sh_size) > fileSize)
			{
				printf("Error: address too big; patching failed\n", token->str);

				return 3;
			};

			fseek(dstfile, shdr->sh_addr, SEEK_SET);

			t = fwrite(elfData+shdr->sh_offset, 1, shdr->sh_size, dstfile);

			if (t != shdr->sh_size)
			{
				printf("Error writing file; patching failed\n");
				return 3;
			};
		};

		count--;

		p += ehdr->e_shentsize;

		shdr = (Elf32_Shdr*)p;
	};

	fclose(dstfile);
	fclose(elfFile);

	printf("\nPatching OK\n");

	return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
