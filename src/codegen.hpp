#pragma once
#include "ast.hpp"

class codegen
{
public:
	codegen(List<Variable*>& globals,
		List<Function*>& functions);

	void generate();

	void visit(Statement* stmt);
	void visit_block(Block* blk);
	void visit_assign(Assignment* asgn);
	void visit_factor(Factor* factor);
	void visit_left_expression(LeftExpression* lexp);
	void visit_chained_expression(ChainedExpression* cexp);
	void visit_integer_literal(IntegerLiteral* literal);
	void visit_call(CallStmt* call);
	void visit_return(ReturnStmt* ret);

private:
	List<Variable*>& globals;
	List<Function*>& functions;
};
