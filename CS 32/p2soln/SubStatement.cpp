#include "SubStatement.h"
#include "ProgramState.h"


// SubStatement.cpp:
SubStatement::SubStatement(char variableName, int value)
	: variableName( variableName ), value( value )
{}

void SubStatement::execute(ProgramState * state, std::ostream &outf)
{
	int val = state->getValue( variableName );
	state->setValue( variableName, val - value );
	state->nextLine();	
}

