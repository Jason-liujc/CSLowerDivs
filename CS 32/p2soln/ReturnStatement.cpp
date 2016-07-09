#include "ReturnStatement.h"
#include <iostream>
#include <cstdlib>

ReturnStatement::ReturnStatement()
{}

void ReturnStatement::execute(ProgramState * state, std::ostream &outf)
{
	if( ! state->canReturn() )
	{
		outf << "Illegal return statement\n";
		exit(1);
	}
	state->setLine( state->returnLine() );
	state->nextLine();
}

