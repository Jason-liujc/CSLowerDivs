#include "DivStatement.h"
#include <iostream>
#include <cstdlib>

DivStatement::DivStatement(char variableName, int value)
	: variableName( variableName ), value( value )
{}

void DivStatement::execute(ProgramState * state, std::ostream &outf)
{
	int val = state->getValue( variableName );
	if ( value == 0 )
	{
		outf << "Divide by zero exception\n";
		exit(1);
	}
	state->setValue( variableName, val / value );
	state->nextLine();	
}

