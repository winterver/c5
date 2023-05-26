#include <stdio.h>
#include <vector>
#include <string>

#include "vm.hpp"
#include "image.hpp"
#include "parser.hpp"
#include "tokens.hpp"
#include "string_pool.hpp"
#include "instructions.hpp"

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

	/*
	for(auto t : toks)
	{
		printf("%d: %d\n", t.lineno, t.tok);
	}
	*/
	
	image img;
	parser pr(img, toks.data());
	pr.parse();

	/*
	for(auto&x : pr.gvars)
	{
		printf("%d %d* %s, addr = %d\n", 
			x.tinfo.type, x.tinfo.depth, x.name, x.addr);
	}

	for(auto& x : pr.funcs)
	{
		printf("%d %d* %s(", x.tinfo.type, x.tinfo.depth, x.name);
		for(auto& p : x.params)
		{
			printf("%d %d* %s, ", p.tinfo.type, p.tinfo.depth, p.name);
		}
		printf("), addr = %d\n", x.addr);
	}

	for(u8 x : img.text)
	{
		printf("%02X ", x);
	}
	*/

	/*image img2;
	img2.fill_text(
		JMP, u32(18),
		IMD, i32(123),
		PUQ,
		IMD, i32(-110),
		MUL,
		RET,
		CAL, u32(5),
		PRTF,
		EXIT
	);*/

	vm_t vm(img);
	vm.exec();
}
