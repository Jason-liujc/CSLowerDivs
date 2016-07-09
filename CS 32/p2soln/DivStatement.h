#ifndef __DIV_STATEMENT_H
#define __DIV_STATEMENT_H

#include "Statement.h"
#include "ProgramState.h"

class DivStatement: public Statement
{
private:
	char variableName;
	int value;


public:
	DivStatement(char variableName, int value);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

