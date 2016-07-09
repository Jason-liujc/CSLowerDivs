#include "EndProgramStatement.h"
#include <cstdlib>

EndProgramStatement::EndProgramStatement()
{}

void EndProgramStatement::execute(ProgramState * state, std::ostream &outf)
{
	exit(1);
}

