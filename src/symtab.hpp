#pragma once

#define CATEGORY_VAR 1 // simple variable
#define CATEGORY_ARRAY 2
#define CATEGORY_FUNC 3

#define TYPE_VOID 1
#define TYPE_CHAR 2
#define TYPE_SHORT 3
#define TYPE_INT 4
#define TYPE_LONG 5
#define TYPE_STRUCT 6
#define TYPE_TYPEDEF 7 // used by parser. never occurs in symbol table

#define SPECIF_CONST 1
#define SPECIF_STATIC 2
#define SPECIF_TYPEDEF 4

struct param_t
{
	param_t* next;
	const char* name;
	int type;
	int specif; // specifiers & qualifiers.
	int depth; // depth of the pointer. 0 indicates non-pointer
	// array in parameter list is not supported
};

struct initial_t
{
	// TODO
};

struct init_decl_t {
	init_decl_t* next;
	int category;
	const char* name;
	int depth;
	param_t* params;
	bool variadic;
	initial_t* init;
};

struct sym_t
{
	sym_t* next;
	int category;
	const char* name;
	int scope;

	int type;
	int specif; // specifiers & qualifiers.
	int depth; // depth of the pointer. 0 indicates non-pointer
	
	param_t* params;
	bool variadic;
};

sym_t* insert(const char* name);
sym_t* lookup(const char* name);
sym_t* lookup_type(const char* name);
void print_table();

void next_scope();
void exit_scope();
