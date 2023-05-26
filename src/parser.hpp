#pragma once
#include <vector>

struct token
{
	int tok;
	int lineno;
	union {
		long long int ival;
		long double fval;
		char* sval;
	};
};

struct typeinfo
{
	int type;
	char* struct_name;
	int depth;

	bool operator==(typeinfo& rhs);
	bool operator!=(typeinfo& rhs);
};

struct param
{
	typeinfo tinfo;
	char* name;
	int addr;
};

class param_set : public std::vector<param>
{
public:
	param* get(char* name);
	bool operator==(param_set& rhs);
	bool operator!=(param_set& rhs);
};

struct function
{
	typeinfo tinfo;
	char* name;
	param_set params;
	int addr;
};

struct variable
{
	typeinfo tinfo;
	char* name;
	int addr;
};

class variable_set : public std::vector<variable>
{
public:
	variable_set* const parent;

	variable_set(variable_set* parent = nullptr);
	variable* get(char* name); // doesn't search parent
	variable* search(char* name); // searches parent
};

class function_set : public std::vector<function>
{
public:
	function* get(char* name);
};

class buffer;
class image;

class parser
{
public:
	parser(image& img, struct token* tok);

	void parse();

private:
	void error(const char* errmsg);
	void get_variable(char* name, int& addr, int& clazz); 
		// helper function
		// clazz = 0, not found
		// clazz = 1, local
		// clazz = 2, param
		// clazz = 3, global

	void access(char* name, int& size); 
		// load the address of specified variable
	
	function* get_function(char* name);

	struct token* tok;

	typeinfo tinfo; // updated after a call to type()
	param_set params; // updated after a call to paramlist()
					  //
	function* curfunc; // updated after parsing a function signature	
					   // or when calling a function

	int npassed;	// num of arguments passed during a call 
	int call_stack_size;

	variable_set* curlocal;
	int localoffset; // an offset relative bp, where the latest local
					 // variable should be placed

	int token();
	void match(int t);

	void program();
	void type();
	void depth();
	void structdef();
	void gvardef();
	void funcdef();
	void paramlist();
	void block();
	void lvardef();
	void assign();
	void call(buffer& buf);
	void arglist(buffer& buf);
	void expression(buffer& buf);
	void term1(buffer& buf);
	void term2(buffer& buf);
	void factor(buffer& buf);

public:
	image& img;
	function_set funcs;
	variable_set gvars;
};
