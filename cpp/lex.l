%{

#include "token.h"

Token token;

int yywrap()
{
	return 1;
}

%}

SPACE			[\t\v ]
SPACES			({SPACE}+)

LETTER			[A-Za-z_]
DIGIT			[0-9]
DIGITS			({DIGIT}+)
OCTDIGIT		[0-7]
HEXDIGIT		[0-9A-Fa-f]
NOTLD			(^({DIGIT}|{LETTER}))


DECCONST		({DIGITS})
OCTCONST		("0"{OCTDIGIT}+[Ll]?)
HEXCONST		("0"[xX]{HEXDIGIT}+[Ll]?)
INTCONST		(({DECCONST}|{OCTCONST}|{HEXCONST})[Ll]?)

STRINGCONST		(\"([\x20-\x21]|[\x23-\xFF])*\")

ASSIGN			"="
COMMA			","

FILENAME		(([\x21]|[\x23-\x2B]|[\x2D-\x3C]|[\x3E-\xFF])+)



%%

{SPACES}		{              }



{ASSIGN}		{ token.str = yytext; return token.id = ASSIGN; }
{COMMA}			{ token.str = yytext; return token.id = COMMA; }

{INTCONST}		{ token.str = yytext; return token.id = NUM; }
{STRINGCONST}	{ token.str = yytext; return token.id = STR; }
{FILENAME}		{ token.str = yytext; return token.id = FILENAME; }

<<EOF>>			{ token.str = 0; return token.id = 0; }


%{ /*

*/
%}

%%

int SetScanBuffer(char *base, int size)
{
	return yy_scan_buffer(base, size) != 0;
}


const Token* GetToken()
{
	yylex();

	return &token; 
}


