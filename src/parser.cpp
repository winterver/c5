#include <stdio.h>
#include <stdlib.h>

#include "types.hpp"
#include "image.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "string_pool.hpp"
#include "instructions.hpp"

bool typeinfo::operator==(typeinfo& rhs)
{
	return (type == rhs.type
		&& struct_name == rhs.struct_name
		&& depth == rhs.depth);
}

bool typeinfo::operator!=(typeinfo& rhs)
{
	return !this->operator==(rhs);
}

param* param_set::get(char* name)
{
	auto r = std::find_if(begin(), end(),
		[name] (auto& x) { return name == x.name; });
	return r != end() ? &(*r) : nullptr;
}

bool param_set::operator==(param_set& rhs)
{
	if (size() != rhs.size())
	{
		return false;
	}

	for(int i = 0; i < size(); i++)
	{
		if (at(i).tinfo != rhs[i].tinfo)
		{
			return false;
		}
	}
	return true;
}

bool param_set::operator!=(param_set& rhs)
{
	return !this->operator==(rhs);
}

variable* variable_set::get(char* name)
{
	auto r = std::find_if(begin(), end(),
		[name] (auto& x) { return name == x.name; });
	return r != end() ? &(*r) : nullptr;
}

function* function_set::get(char* name)
{
	auto r = std::find_if(begin(), end(),
		[name] (auto& x) { return name == x.name; });
	return r != end() ? &(*r) : nullptr;
}

parser::parser(image& img, struct token* tok)
	: img(img)
	, tok(tok)
{ }

void parser::parse()
{
	// setup entry
	img.fill_text(CAL, u32(), EXIT);
	// parse & code generation
	program();

	// set the operand of the CAL to addr of main()
	char* name = string_pool::get_instance().add("main");
	function* main = funcs.get(name);

	if (main != nullptr)
	{
		if (main->addr == -1)
		{
			error("main() not implemented");
		}
		*(u32*)&img.text[1] = main->addr;
	}
	else
	{
		error("main() not found");
	}
}

void parser::error(const char* errmsg)
{
	printf("(%d) %s\n", tok->lineno, errmsg);
	exit(-1);
}

int parser::token()
{
	return tok->tok;
}

void parser::match(int t)
{
	if (t == token())
	{
		tok++;
	}
	else
	{
		error("token mismatch");
	}
}

void parser::program()
{
	while(token())
	{
		struct token* prev = tok;
		type();
		depth();
		match(IDENTIFIER);
		int next = token();
		tok = prev;

		if (next == '{')
		{
			structdef();
		}
		else if (next == '(')
		{
			funcdef();
		}
		else
		{
			gvardef();
		}	
	}
}

void parser::type()
{
	switch(token())
	{
	case CHAR:
	case SHORT:
	case INT:
	case LONG:
		tinfo.type = token();
		match(tinfo.type);
		tinfo.struct_name = nullptr;
		break;
	case STRUCT:
		tinfo.type = STRUCT;
		match(STRUCT);
		tinfo.struct_name = tok->sval;
		match(IDENTIFIER);
		break;
	default:
		error("a type needed");
	}
}

void parser::depth()
{
	for(tinfo.depth = 0; token() == '*'; tinfo.depth++)
	{
		match('*');
	}
}

void parser::structdef()
{
	match(STRUCT);
	match(IDENTIFIER);
	match('{');
	match('}');
	match(';');
}

void parser::funcdef()
{
	type();
	depth();
	typeinfo ret_type = tinfo;
	char* name = tok->sval;
	match(IDENTIFIER);
	paramlist();

	function func;	
	func.tinfo = tinfo;
	func.name = name;
	func.params = params;
	func.addr = -1; // -1 indicates forward declaration

	// check if the declaration already exists,
	function* decl = funcs.get(name);

	// if yes, check if both declaration are the same
	if (decl != nullptr)
	{	
		if (decl->tinfo != func.tinfo
			|| decl->params != func.params)
		{
			error("declaration mismatch");
		}
	}

	// if it's a function definition
	if (token() == '{')
	{
		if (decl != nullptr)
		{
			// check if the found declaration
			// has function body
			if (decl->addr != -1)
			{
				error("function redefinition");
			}
		}

		// get start address of the function body
		func.addr = img.text.size();

		// register/update function info
		if (decl == nullptr)
		{
			funcs.push_back(func);
		}
		else
		{
			decl->addr = func.addr;
			// update parameter names
			decl->params = std::move(func.params);
		}
		
		// parse function body
		curfunc = &func;
		block();	
	}
	else
	{
		// else it's a forward declaration
		match(';');

		if (decl == nullptr)
		{
			funcs.push_back(func);
		}
	}	
}

void parser::gvardef()
{
	type();

NextVar:
	depth();
	char* name = tok->sval;
	match(IDENTIFIER);

	variable var;
	var.tinfo = tinfo;
	var.name = name;	

	if (gvars.get(var.name))
	{
		error("global variable redefinition");
	}
	else
	{
		// alloc memory for the variable in data
		var.addr = img.data.size();
		// TODO support initialization
		// TODO support struct & string & array & float
		if (var.tinfo.depth == 0)
		{
			switch(var.tinfo.type)
			{
			case CHAR: img.fill_data(i8()); break;
			case SHORT: img.fill_data(i16()); break;
			case INT: img.fill_data(i32()); break;
			case LONG: img.fill_data(i64()); break;
			default: error("unsupported type"); break;
			}
		}
		else
		{
			img.fill_data(u64());
		}
		gvars.push_back(var);
	}
	
	if (token() == ',')
	{
		match(',');	
		goto NextVar;	
	}
	match(';');
}

void parser::paramlist()
{
	params.clear();

	match('(');

	if (token() == ')')
	{
		match(')');
		return;
	}	

NextParam:	
	type();
	depth();
	char* name = tok->sval;
	match(IDENTIFIER);

	param p;
	p.tinfo = tinfo;
	p.name = name;

	if (params.get(p.name))
	{
		error("local variable redefinition");
	}
	params.push_back(p);

	if (token() == ',')
	{
		match(',');
		goto NextParam;
	}

	match(')');
}

void parser::block()
{
	match('{');
	
	variable_set locals;

	img.fill_text(RET);
	
	match('}');
}
