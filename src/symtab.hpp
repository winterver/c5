#pragma once

#define CATEGORY_VAR 1
#define CATEGORY_FUNC 2

struct param_t
{
	int type;
	int depth;
	const char* name;
};

struct sym_t
{
	sym_t* next;
	int category;
	const char* name;
	int scope;

	int type;
	int depth;
	
	int nparams;
	param_t* params;
	bool variadic;
};

sym_t* insert(const char* name);
sym_t* lookup(const char* name);
sym_t* lookup_type(const char* name);

void next_scope();
void exit_scope();
