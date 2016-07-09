#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
class ProgramState;

class SubStatement: public Statement
{
private:
	char variableName;
	int value;


public:
	SubStatement(char variableName, int value);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



