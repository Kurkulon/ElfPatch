#ifndef TOKEN_H__14_04_2016__22_23
#define TOKEN_H__14_04_2016__22_23

typedef enum  { ASSIGN = 1, COMMA = 2, NUM = 3, STR = 4, FILENAME = 5 } TKN_ID;

typedef struct 
{
	int id;
	const char *str;
} Token;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif // TOKEN_H__14_04_2016__22_23
