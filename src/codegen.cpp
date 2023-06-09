#include "codegen.hpp"
#include <typeinfo>

codegen::codegen(
	List<Variable*>& globals, 
	List<Function*>& functions
)
	: globals(globals)
	, functions(functions)
{ }

void codegen::generate()
{
	for(auto func : functions)
	{
		visit(func->body);
	}
}

void codegen::visit(Statement* stmt)
{
#define VISIT(type, visitor) \
	(dynamic_cast<type>(stmt)) \
	{ visitor((type) stmt); }

	if VISIT(Block*, visit_block)
	else if VISIT(Assignment*, visit_assign)
	else if VISIT(LeftExpression*, visit_left_expression)
	else if VISIT(ChainedExpression*, visit_chained_expression)
	else if VISIT(IntegerLiteral*, visit_integer_literal)
	else if VISIT(CallStmt*, visit_call)
	else if VISIT(ReturnStmt*, visit_return)
	else { printf("unknown node: %s\n", typeid(*stmt).name()); }

#undef VISIT
}

void codegen::visit_block(Block* blk)
{
	for(auto stmt : blk->stmts)
	{
		visit(stmt);
	}
}

void codegen::visit_assign(Assignment* asgn)
{
	visit(asgn->right);
	printf("PUQ\n");
	visit(asgn->left);
	printf("STD\n"); // TODO
}

void codegen::visit_left_expression(LeftExpression* lexp)
{
	printf("LEA %s\n", lexp->var->name);
}

void codegen::visit_chained_expression(ChainedExpression* cexp)
{
	visit(cexp->lhs);
	for(auto rhs : cexp->rhs)
	{
		printf("LOD\n"); //TODO
		printf("PUQ\n");
		visit(rhs.second);
		printf("LOD\n"); //TODO
		switch(rhs.first)
		{
		case '+': printf("ADD\n"); break;
		case '-': printf("SUB\n"); break;
		case '*': printf("MUL\n"); break;
		case '/': printf("DIV\n"); break;
		}
	}
}

void codegen::visit_integer_literal(IntegerLiteral* literal)
{
	printf("IMD %lld\n", literal->value);
}

void codegen::visit_call(CallStmt* call)
{
	auto rbeg = call->args.rbegin();
	auto rend = call->args.rend();

	for(; rbeg != rend; rbeg++)
	{
		visit(*rbeg);
		if (dynamic_cast<LeftExpression*>(*rbeg))
		{
			printf("LOD\n"); //TODO
		}
		printf("PUD\n"); //TODO
	}
	printf("CAL %s\n", call->func->sig->name);
}

void codegen::visit_return(ReturnStmt* ret)
{
	if (ret->expr)
	{
		visit(ret->expr);
		if (dynamic_cast<LeftExpression*>(ret->expr))
		{
			printf("LOD\n"); //TODO
		}
	}
	printf("RET\n");
}
