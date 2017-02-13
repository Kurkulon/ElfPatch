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

extern "C" const Token* GetToken();
extern "C" int SetScanBuffer(char *base, int size);
dfg
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

//bool parsePatch(const std::string& token)
//{
//  size_t equalIndex = token.find_first_of('=');
//  
//  if (equalIndex == string::npos)
//    return false;
//    
//  Patch patch;
//  patch.address = strtoul(token.substr(0, equalIndex).c_str(), NULL, 16);
//
//  string values = token.substr(equalIndex+1);
//  size_t startIndex = 0;
//  size_t commaIndex;
//
//  while ((commaIndex = values.find_first_of(',', startIndex)) != string::npos)
//  {
//    byte value = strtoul(values.substr(startIndex, commaIndex).c_str(), NULL, 16);
//    startIndex = commaIndex + 1;
//    patch.values.push_back(value);
//  }
//  
//  byte value = strtoul(values.substr(startIndex).c_str(), NULL, 16);
//  patch.values.push_back(value);
//  
//  entries.push_back(patch);
//  
//  return true;
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static u32 adr = 0;
static u32 fileSize = 0;
static FILE* srcfile = 0;
static byte srcbuf[1024];
static u32 srcfileSize = 0;


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

	const char* filename = token->str;


	FILE* dstfile = fopen(filename, "r+b");

	if (!dstfile)
	{
		printf("Unable to open file %s. Exiting.\n", filename);
		return 1;
	}

	fseek(dstfile, 0L, SEEK_END);
	fileSize = ftell(dstfile);

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
