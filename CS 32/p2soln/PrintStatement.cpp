#include "PrintStatement.h"
#include <iostream>

PrintStatement::PrintStatement(char variableName)
	: variableName( variableName )
{}


void PrintStatement::execute(ProgramState * state, std::ostream &outf)
{
	int val = state->getValue( variableName );
	outf << val << std::endl;
	state->nextLine();
}

