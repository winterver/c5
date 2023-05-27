#pragma once
#include <vector>
#include <sstream>

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
	bool hasbody;
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

class codebuf : public std::ostringstream
{
public:
	void fill(int op)
	{
		(*this) << op << "\n";
	}
	void fill(int op, long long int num)
	{
		(*this) << op << " " << num << "\n";
	}
	void fill(int op, const char* label)
	{
		(*this) << op << " " << label << "\n";
	}
};

class parser
{
public:
	void parse(struct token* tok);

private:
	// helper functions
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

	// parser
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
	int globaloffset; // an offset relative data, ditto but for global.

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
	void call(codebuf& buf);
	void arglist(codebuf& buf);
	void expression(codebuf& buf);
	void term1(codebuf& buf);
	void term2(codebuf& buf);
	void factor(codebuf& buf);

public:
	codebuf cb;
	function_set funcs;
	variable_set gvars;
};
