%option noyywrap
%option yylineno
%option nounistd

%{
#include "y.tab.h"
#ifdef _WIN32
#  include <io.h>
#  define isatty _isatty 
#endif

void yyerror(const char* s);
static const char* pool(const char* name);
%}

%%

	/* primitives */
"void"								{ return VOID; }
"char"								{ return CHAR; }
"short"								{ return SHORT; }
"int"								{ return INT; }
"long"								{ return LONG; }
"float"								{ return FLOAT; }
"double"							{ return DOUBLE; }
	/* keywords */
	/*"struct"							{ return STRUCT; }*/
"return"							{ return RETURN; }

[a-zA-Z_][a-zA-Z_0-9]*				{
										yylval.sval = pool(yytext);
										return ID;
									}

0|[1-9][0-9]*						{ return NUM; }
0[1-7][0-7]*						{ return NUM; }
0(x|X)[0-9a-fA-F]+					{ return NUM; }
\"([^\\\"]|\\.)*\"  				{ return STR; }
(0|[1-9][0-9]*)\.([0-9]+|[0-9]*f)	{ return DEC; }

	/* single-character operators & symbols */
[~!%^&*()\-+={}\[\]|;:<>,./]		{ return *yytext; }

	/* multi-character operators */
"=="								{ return EQ; }
"!="								{ return NE; }
">="								{ return GE; }
"<="								{ return LE; }
"+="								{ return PLUSASGN; }
"-="								{ return MINUSASGN; }
"*="								{ return MULASGN; }
"/="								{ return DIVASGN; }
"%="								{ return MODASGN; }
"&="								{ return ANDASGN; }
"|="								{ return ORASGN; }
"^="								{ return XORASGN; }
"&&"								{ return LOGAND; }
"||"								{ return LOGOR; }
"<<"								{ return SHL; }
">>"								{ return SHR; }
"<<="								{ return SHLASGN; }
">>="								{ return SHRASGN; }
"++"								{ return INCR; }
"--"								{ return DECR; }
"->"								{ return ARW; }
	/* TODO: '...' */

	/* comments & skips & error handle */
"//".*								{ /* DO NOTHING */ }
[ \r\t\n\v]							{ /* DO NOTHING */ }
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]	{ /* DO NOTHING */ }
[/][*]								{ yyerror("unclosed comment"); }
.									{ yyerror("unknown character"); }

%%

#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_set>

void yyerror(const char* s)
{ 
	printf("(%d) %s", yylineno, s); 
	exit(-1); 
}

// string pool
static const char* pool(const char* text)
{
	struct string_compare { 
		bool operator()(
			const char* s1, 
			const char* s2
		) const {
			return !strcmp(s1, s2);
		}
	};

	static std::unordered_set<
		const char*,
		std::hash<std::string>,
		string_compare
	> strings;
	
	auto it = strings.find(text);
	if (it != strings.end())
	{
		return *it;
	}

	char* dup = strdup(text);
	strings.insert(dup);
	return dup;
}
