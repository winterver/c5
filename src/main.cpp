#include <stdio.h>
#include <vector>
#include <string>

#include "vm.hpp"
#include "image.hpp"
#include "parser.hpp"
#include "tokens.hpp"
#include "instructions.hpp"

void yyrestart ( FILE *input_file  );
int yylex (void);
extern int yyleng;
extern char* yytext;
extern int yylineno;

class {
public:
	char* add(const char* s)
	{
		for(auto x : strs)
		{
			if (!strcmp(x, s))
			{
				return x;
			}
		}
		strs.push_back(strdup(s));
		return strs.back();
	}
private:
	std::vector<char*> strs;
} strpool;

void tokenize(std::vector<token>& toks, FILE* in = stdin)
{
	yyrestart(in);
	while(true)
	{
		struct token tok = { };
		tok.tok = yylex();

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

	for(auto t : toks)
	{
		printf("%d\n", t.tok);
	}

	/*
	image img;
	img.fill_text(
		JMP, u32(18),
		IMD, i32(123),
		PUQ,
		IMD, i32(-110),
		MUL,
		RET,
		CAL, u32(5),
		PRTF,
		EXIT
	);

	vm_t vm(img);
	vm.exec();
	*/
}
