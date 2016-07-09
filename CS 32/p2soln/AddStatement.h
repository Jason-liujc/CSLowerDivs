#ifndef __ADD_STATEMENT_H
#define __ADD_STATEMENT_H

#include "Statement.h"
#include "ProgramState.h"

class AddStatement: public Statement
{
private:
	char variableName;
	int value;


public:
	AddStatement(char variableName, int value);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

