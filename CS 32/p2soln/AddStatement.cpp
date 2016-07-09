#include "AddStatement.h"

AddStatement::AddStatement(char variableName, int value)
	: variableName( variableName ), value( value )
{}

void AddStatement::execute(ProgramState * state, std::ostream &outf)
{
	int val = state->getValue( variableName );
	state->setValue( variableName, val + value );
	state->nextLine();	
}

