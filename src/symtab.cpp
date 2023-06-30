#include "symtab.hpp"
#include <string.h>
#include <stdio.h>

void yyerror(const char* s);

#define SIZE 211
#define CHARS 67

// polynomial rolling
static int hash(const char* name)
{
	unsigned long long val = 0;
	unsigned long long pow = 1;
	for (; *name; name++)
	{
		val = (val + *name * pow) % SIZE;
		pow = pow * CHARS % SIZE;
	}
	return val;
}

static sym_t* table[SIZE] = {0};
static int scope = 0;

sym_t* insert(const char* name)
{
	int hashval = hash(name);
	sym_t* l = table[hashval];

	// string pool is installed in lexer.l
	// all char* variables with the same string content
	// hold the same address. so strings can be compared
	// directly. no need to use strcmp().
	while (l != nullptr && l->name != name) l = l->next;

	if (l != nullptr && l->scope == scope)
	{
		yyerror("variable redefinition");
	}

	l = new sym_t;
	l->name = name;
	l->scope = scope;
	// more members to be initialized in parser
	// ...

	l->next = table[hashval];
	table[hashval] = l;

	return l;
}

sym_t* lookup(char* name)
{
	int hashval = hash(name);
	sym_t* l = table[hashval];
	while (l != nullptr && l->name == name) l = l->next;
	return l;
}

sym_t* lookup_type(const char* name)
{
	int hashval = hash(name);
	sym_t*l = table[hashval];

	while (l != nullptr)
	{
		if (l->specif & SPECIF_TYPEDEF && l->name == name)
		{
			return l;
		}
		l = l->next;
	}
	return nullptr;
}

void next_scope()
{
	scope++;
}

void exit_scope()
{
	for (int i = 0; i < SIZE; i++){
		sym_t* l = table[i];
		/* Find the first item that is from another scope */
		while(l != nullptr && l->scope == scope)
		{
			l = l->next;
		}
		/* Set the list equal to that item */
		table[i] = l;
	}
	scope--;
}
