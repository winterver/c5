#pragma once

#define CATEGORY_VAR 1 // simple variable
#define CATEGORY_ARRAY 2
#define CATEGORY_FUNC 3
#define CATEGORY_TYPEDEF 4 // typedef

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
	//struct_t *struc; // valid only if type == TYPE_STRUCT
	int specif; // specifiers & qualifiers.
	int depth; // depth of the pointer. 0 indicates non-pointer
	
	// array in parameter list is not supported
};

struct dimen_t
{
	dimen_t* next;
	int len; // 0 indicates it's determined by its initializer list.
};

struct sym_t
{
	sym_t* next;
	int category;
	const char* name;
	int scope;

	int type;
	//struct_t *struc; // valid only if type == TYPE_STRUCT
	int specif; // specifiers & qualifiers.
	int depth; // depth of the pointer. 0 indicates non-pointer

	dimen_t* dims;
	param_t* params;
};

sym_t* insert(const char* name);
sym_t* lookup(const char* name);
sym_t* lookup_type(const char* name);

void next_scope();
void exit_scope();
