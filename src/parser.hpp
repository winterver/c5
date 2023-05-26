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
	variable* get(char* name);
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

	struct token* tok;
	function* curfunc;
	typeinfo tinfo;
	param_set params;

	int token();
	void match(int t);

	void program();
	void type();
	void depth();
	void structdef();
	void funcdef();
	void gvardef();
	void paramlist();
	void block();

public:
	image& img;
	function_set funcs;
	variable_set gvars;
};
