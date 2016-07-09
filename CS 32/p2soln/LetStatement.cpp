// LetStatement.cpp:
#include "LetStatement.h"
using namespace std;

LetStatement::LetStatement(char variableName, int value)
	: variableName( variableName ), value( value )
{}


// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
//
// There is no way for a LET statement to fail, so there is no reason for
// it to ever throw a FatalException.  Nevertheless, the signature of the
// method must match the signature of the execute() method in Statement,
// so we'll leave the "throws" clause alone.
void LetStatement::execute(ProgramState * state, ostream &outf)
{
	// Remove code from within from the "given" section.
	state->setValue( variableName, value );
	state->nextLine();	
}


