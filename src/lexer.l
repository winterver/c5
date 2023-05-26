%option noyywrap
%option yylineno
%option nounistd

%{
#include "tokens.hpp"
#ifdef _WIN32
#  include <io.h>
#  define isatty _isatty 
#endif
void yyerror(const char* s);
%}

%%

	/* primitives */
"void"								{ return VOID; }
"char"								{ return CHAR; }
"short"								{ return SHORT; }
"int"								{ return INT; }
"long"								{ return LONG; }
	/* keywords */
"struct"							{ return STRUCT; }
"return"							{ return RETURN; }

[a-zA-Z_][a-zA-Z_0-9]*				{ return IDENTIFIER; }
0|[1-9][0-9]*						{ return NUMBER; }
0[1-7][0-7]*						{ return NUMBER; }
0(x|X)[0-9a-fA-F]+					{ return NUMBER; }
\"([^\\\"]|\\.)*\"  				{ return STRING; }
(0|[1-9][0-9]*)\.([0-9]+|[0-9]*f)	{ return DECIMAL; }

	/* single-character operators & symbols */
[~!%^&*()-+={}\[\]|;:<>,./]			{ return *yytext; }

	/* multi-character operators */
"=="								{ return EQUAL; }
"!="								{ return NOT_EQUAL; }
">="								{ return GREATER_EQUAL; }
"<="								{ return LESS_EQUAL; }
"+="								{ return PLUS_ASSIGN; }
"-="								{ return MINUS_ASSIGN; }
"*="								{ return MUL_ASSIGN; }
"/="								{ return DIV_ASSIGN; }
"%="								{ return MOD_ASSIGN; }
"&="								{ return AND_ASSIGN; }
"|="								{ return OR_ASSIGN; }
"^="								{ return NOT_ASSIGN; }
"&&"								{ return LOGIC_AND; }
"||"								{ return LOGIC_OR; }
"<<"								{ return LSHIFT; }
">>"								{ return RSHIFT; }
"<<="								{ return LSHIFT_ASSIGN; }
">>="								{ return RSHIFT_ASSIGN; }
"++"								{ return INCREASE; }
"--"								{ return DECREASE; }
"->"								{ return ARROW; }
"..."								{ return ELLIPSIS; }

	/* comments & skips & error handle */
"//".*								{ /* DO NOTHING */ }
[ \r\t\n\v]							{ /* DO NOTHING */ }
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]	{ /* DO NOTHING */ }
[/][*]								{ yyerror("unclosed comment"); }
.									{ yyerror("unknown character"); }

%%

#include <stdio.h>
void yyerror(const char* s)
{ 
	puts(s); 
	exit(-1); 
}
