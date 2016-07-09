#ifndef RETURN_STATEMENT_INCLUDED
#define RETURN_STATEMENT_INCLUDED

#include "Statement.h"

class ProgramState;

class ReturnStatement: public Statement
{
private:
	int linenum;


public:
	ReturnStatement();
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};


#endif

