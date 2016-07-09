#include "GotoStatement.h"
#include <iostream>
#include <cstdlib>


GotoStatement::GotoStatement(int linenum)
	: linenum( linenum )
	{}
	
void GotoStatement::execute(ProgramState * state, std::ostream &outf)
{
	if ( linenum > 0 && linenum <= state->maxLineNum() )
		state->setLine( linenum );
	else
	{
		outf << "Illegal jump instruction\n";
		exit(1);
	}		
}

