#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>

//#include "vm.hpp"

int yylex(void);
extern int yyleng;
extern char* yytext;
extern int yylineno;
void yyrestart(FILE *in);

void tokenize(FILE* in = stdin)
{
	yyrestart(in);
	string_pool& strpool = string_pool::get_instance();

	while(true)
	{
		int token = yylex();

		switch(tok.tok)
		{
		case ID: tok.sval = strpool.add(yytext); break;
		case NUM: tok.ival = std::stoll(yytext, nullptr, 0); break;
		case DEC: tok.fval = std::stod(yytext);
		case STR: // TODO process escape sequences
			yytext[yyleng-1] = 0; 
			tok.sval = strpool.add(yytext+1); 
			break;
		}

		if (tok.tok == 0)
		{
			break;
		}
	}
}

int main()
{
	tokenize();
}
