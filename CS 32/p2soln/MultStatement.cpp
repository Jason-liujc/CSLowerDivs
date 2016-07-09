#include "MultStatement.h"

MultStatement::MultStatement(char variableName, int value)
	: variableName( variableName ), value( value )
{}

void MultStatement::execute(ProgramState * state, std::ostream &outf)
{
	int val = state->getValue( variableName );
	state->setValue( variableName, val * value );
	state->nextLine();	
}

