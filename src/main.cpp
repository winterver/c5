#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "vm.hpp"
#include "image.hpp"
#include "parser.hpp"
#include "tokens.hpp"
#include "string_pool.hpp"
#include "instructions.hpp"
#include "assembler.hpp"

int yylex(void);
extern int yyleng;
extern char* yytext;
extern int yylineno;
void yyrestart(FILE *in);

void tokenize(std::vector<token>& toks, FILE* in = stdin)
{
	yyrestart(in);
	string_pool& strpool = string_pool::get_instance();

	while(true)
	{
		token tok = { };
		tok.tok = yylex();
		tok.lineno = yylineno;

		switch(tok.tok)
		{
		case IDENTIFIER: tok.sval = strpool.add(yytext); break;
		case NUMBER: tok.ival = std::stoll(yytext, nullptr, 0); break;
		case DECIMAL: tok.fval = std::stod(yytext);
		case STRING: // TODO process escape characters
			yytext[yyleng-1] = 0; 
			tok.sval = strpool.add(yytext+1); 
			break;
		}
		toks.push_back(tok);

		if (tok.tok == 0)
		{
			break;
		}
	}
}

int main()
{
	std::vector<token> toks;
	tokenize(toks);
	
	parser pr;
	pr.parse(toks.data());

	//print_assembly(pr.cb.str());
	image img = assemble(pr.cb.str());
	img.data.reserve(1024);

	/*
	printf("total size: %zd\n", img.text.size());
	for(u8 x : img.text)
	{
		printf("%d ", x);
	}
	*/

	vm_t vm(img);
	vm.exec();
}
