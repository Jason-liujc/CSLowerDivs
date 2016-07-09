#ifndef __END_PROGRAM_STATEMENT_H
#define __END_PROGRAM_STATEMENT_H

#include "Statement.h"

class EndProgramStatement : public Statement
{
public:
	EndProgramStatement();
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

