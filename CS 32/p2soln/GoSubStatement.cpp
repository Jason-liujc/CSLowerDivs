#include "GoSubStatement.h"
#include <iostream>
#include <cstdlib>

GoSubStatement::GoSubStatement(int linenum)
	: linenum( linenum )
	{}
	
void GoSubStatement::execute(ProgramState * state, std::ostream &outf)
{
	if ( linenum > 0 && linenum <= state->maxLineNum() )
	{
		int cur = state->getCurrentLine( );
		state->pushLine( cur );
		state->setLine( linenum );
	}
	else
	{
		outf << "Illegal jump instruction\n";		
		exit(1);
	}
}

