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

	/* primitives & struct */
"void"								{ return VOID; }
"char"								{ return CHAR; }
"short"								{ return SHORT; }
"int"								{ return INT; }
"long"								{ return LONG; }
"struct"							{ return STRUCT; }

[a-zA-Z_][a-zA-Z_0-9]*				{ return IDENTIFIER; }
0|[1-9][0-9]*						{ return NUMBER; }
0[1-7][0-7]*						{ return NUMBER; }
0(x|X)[0-9a-fA-F]+					{ return NUMBER; }
\"([^\\\"]|\\.)*\"  				{ return STRING; }
(0|[1-9][0-9]*)\.([0-9]+|[0-9]*f)	{ return DECIMAL; }

	/* single-character operators & symbols */
[~!%^&*()-+={}\[\]|;:<>,./]			{ return *yytext; }

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
