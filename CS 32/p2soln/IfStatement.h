#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include <string>

enum Op { GT, GEQ, LT, LEQ, EQ, NEQ };

class IfStatement: public Statement
{
public:
	IfStatement(char variable, std::string op, int comp, int linenum);
	
	virtual void execute(ProgramState * state, std::ostream &outf);

private:
	char variable;
	int comp, linenum;
	Op operation;
	
	bool compare(ProgramState * state);

};

#endif

