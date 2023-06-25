#include "symtab.hpp"
#include <string.h>

#define SIZE 211
#define CHARS 67

void yyerror(const char* s);

// polynomial rolling hash
static int hash(char* name)
{
	unsigned long long val = 0;
	unsigned long long pow = 1;
	for (int i = 0; name[i] != '\0'; i++)
	{
		val = (val + name[i] * pow) % SIZE;
		pow = pow * CHARS % SIZE;
	}
	return val;
}

static sym_t* table[SIZE] = {0};
static int scope = 0;

sym_t* insert(char* name)
{
	int hashval = hash(name);
	sym_t* l = table[hashval];
	while ((l != nullptr) && strcmp(l->name, name)) l = l->next;

	if (l != nullptr && l->scope == scope)
	{
		yyerror("variable redefinition");
	}

	l = new sym_t;
	l->name = strdup(name);
	l->scope = scope;
	// more members to be initialized in parser
	// ...

	l->next = table[hashval];
	table[hashval] = l;

	return l;
}
