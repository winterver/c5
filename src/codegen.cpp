#include "codegen.hpp"
#include <typeinfo>

#define VISIT(stmt, type, visitor) \
	(dynamic_cast<type>(stmt)) \
	{ visitor((type) stmt); }

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
		// TODO
		// print label
		// calculate local stack size
		// replace the variable name after LEA with offset
		visit(func->body);
	}
}

void codegen::visit(Statement* stmt)
{
	if VISIT(stmt, Block*, visit_block)
	else if VISIT(stmt, Assignment*, visit_assign)
	else if VISIT(stmt, ChainedExpression*, visit_chained_expression)
	else if VISIT(stmt, Factor*, visit_factor)
	else if VISIT(stmt, CallStmt*, visit_call)
	else if VISIT(stmt, ReturnStmt*, visit_return)
	else { printf("unknown node: %s\n", typeid(*stmt).name()); }
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
	visit_left_expression(asgn->left);
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
		printf("PUQ\n");
		visit(rhs.second);
		switch(rhs.first)
		{
		case '+': printf("ADD\n"); break;
		case '-': printf("SUB\n"); break;
		case '*': printf("MUL\n"); break;
		case '/': printf("DIV\n"); break;
		}
	}
}

void codegen::visit_factor(Factor* factor)
{
	if VISIT(factor, IntegerLiteral*, visit_integer_literal)
	else if (dynamic_cast<LeftExpression*>(factor))
	{
		visit_left_expression((LeftExpression*) factor);
		printf("LOD\n"); // TODO
	}
	else { printf("unknown node: %s\n", typeid(*factor).name()); }
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
		printf("PUD\n"); //TODO
	}
	printf("CAL %s\n", call->func->sig->name);
}

void codegen::visit_return(ReturnStmt* ret)
{
	if (ret->expr)
	{
		visit(ret->expr);	
	}
	printf("RET\n");
}
