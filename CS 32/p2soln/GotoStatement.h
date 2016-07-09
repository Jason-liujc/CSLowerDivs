#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"

class ProgramState;

class GotoStatement: public Statement
{
private:
	int linenum;


public:
	GotoStatement(int linenum);
	
	virtual void execute(ProgramState * state, std::ostream &outf);
};


#endif

