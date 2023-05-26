#include <stdio.h>
#include <stdlib.h>

#include "types.hpp"
#include "image.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "instructions.hpp"

typeinfo::typeinfo(int type, char* struct_name, int depth)
	: type(type), depth(depth) 
{
	this->struct_name = type == STRUCT 
		? struct_name : nullptr;
}

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

parser::parser(image& img, struct token* tok)
	: img(img)
	, tok(tok)
{ }

void parser::parse()
{
	program();
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
		int type;
		char* struct_name = nullptr;
		int depth;

		// match a type or struct definition
		switch(token())
		{
		case CHAR:
		case SHORT:
		case INT:
		case LONG:
			type = token();
			match(type);
			break;
		case STRUCT:
			{
				type = STRUCT;
				match(STRUCT);
				struct_name = tok->sval;
				match(IDENTIFIER);
				// process struct definition
				if (token() == '{')
				{
					match('{');
					// TODO process struct body
					match('}');
					match(';');
					// next round
					continue;
				}
				// TODO register struct
			}	
			break;
		default:
			error("top-level can only contain "
				"vardef, funcdecl, funcdef or structdef");
		}

		// get the depth of the pointer
		// 0 indicates that it's not a pointer
		for(depth = 0; token() == '*'; depth++)
		{
			match('*');
		}

		// name of the variable or function
		char* name = tok->sval;
		match(IDENTIFIER);

		// if it's a function
		if (token() == '(')
		{
			// match parameter list
			std::vector<param> params;
			paramlist(params);

			function func;	
			func.tinfo = typeinfo(type, struct_name, depth);
			func.name = name;
			func.params = params;
			func.addr = -1; // -1 indicates forward declaration

			// check if the declaration already exists,
			auto decl = std::find_if(
				funcs.begin(), funcs.end(), 
				[&func](auto& rhs) {
					return func.name == rhs.name;	
				}
			);

			// function to compare parameter list
			auto compare = [](
				std::vector<param>& p1,
				std::vector<param>& p2
			)
			{
				if (p1.size() != p2.size())
				{
					return false;
				}

				int size = p1.size();
				for(int i = 0; i < size; i++)
				{
					if (p1[i].tinfo != p2[i].tinfo)
					{
						return false;
					}
				}
				return true;
			};

			// if yes, check if both declaration are the same
			if (decl != funcs.end())
			{	
				if (decl->tinfo != func.tinfo
					|| !compare(decl->params, func.params))
				{
					error("declaration mismatch");
				}
			}

			// if it's a function definition
			if (token() == '{')
			{
				if (decl != funcs.end())
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
				if (decl == funcs.end())
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

				if (decl == funcs.end())
				{
					funcs.push_back(func);
				}
			}
		}
		else
		{
			// else it's a global variable
			
			// TODO register global variable info
			
			while(token() == ',')
			{
				match(',');

				for(depth = 0; token() == '*'; depth++)
				{
					match('*');
				}

				name = tok->sval;
				match(IDENTIFIER);

				// TODO register global variable info
			}
			match(';');
		}
	}
}

void parser::paramlist(std::vector<param>& params)
{
	match('(');

	if (token() == ')')
	{
		match(')');
		return;
	}

	// type of the current param
	int type;
	char* struct_name = nullptr;
	int depth;
	// name of the parameter
	char* name;

NextParam:
	// match a type
	switch(token())
	{
	case CHAR:
	case SHORT:
	case INT:
	case LONG:
		type = token();
		match(type);
		break;
	case STRUCT:
		type = STRUCT;
		match(STRUCT);
		struct_name = tok->sval;
		match(IDENTIFIER);	
		break;
	default:
		error("a type name needed");
	}

	// get the depth of the pointer
	// 0 indicates that it's not a pointer
	for(depth = 0; token() == '*'; depth++)
	{
		match('*');
	}

	name = tok->sval;
	match(IDENTIFIER);

	param p;
	p.tinfo = typeinfo(type, struct_name, depth);
	p.name = name;

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
	match('}');
}
