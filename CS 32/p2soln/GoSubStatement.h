#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "Statement.h"

class ProgramState;

class GoSubStatement: public Statement
{
private:
	int linenum;


public:
	GoSubStatement(int linenum);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};


#endif

