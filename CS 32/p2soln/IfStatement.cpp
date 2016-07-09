#include "IfStatement.h"
#include <iostream>
#include <cstdlib>

using namespace std;

IfStatement::IfStatement(char variable, string op, int comp, int linenum)
	: variable(variable), comp(comp), linenum(linenum)
{
	if ( op == ">=" )
	{
		operation = GEQ;
	}
	else if (op == "<=" )
	{
		operation = LEQ;
	}
	else if (op == "<" )
	{
		operation = LT;
	}
	else if (op == ">")
	{
		operation = GT;
	}
	else if (op == "<>")
	{
		operation = NEQ;
	}
	else// if (op == "=")
	{
		operation = EQ;
	}
}

void IfStatement::execute(ProgramState * state, ostream &outf)
{
	if ( linenum > 0 && linenum <= state->maxLineNum() )
	{
		// make comparison and set line appropriately.
		if ( compare(state) )
		{
			state->setLine( linenum );
		}
		else
		{
			state->nextLine();
		}
	}
	else
	{
		outf << "Illegal jump instruction\n";
		exit(1);
	}
}

bool IfStatement::compare(ProgramState * state)
{
	// returns IF variable operation comp
	int val = state->getValue( variable );
	switch(operation)
	{
		case GEQ:	return val >= comp;
		case LEQ:	return val <= comp;
		case EQ:	return val == comp;
		case LT:	return val <  comp;
		case GT:	return val >  comp;
		default: 	return val != comp;	
	}
}

