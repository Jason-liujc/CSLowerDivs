#include "ProgramState.h"
#include "Stack.h"

const int NUM_VARIABLES = 26;

ProgramState::ProgramState(int numLines)
	: numLines(numLines), programCounter(1)
{
	variables = new int[ NUM_VARIABLES];
	for (int i=0; i < NUM_VARIABLES; i++)
		variables[i] = 0;
}


// Added (removed from given start point)

int ProgramState::getValue(char variable) const
{
	return variables[ variable - 'A' ];
}

void ProgramState::setValue(char variable, int value)
{
	variables[ variable - 'A' ] = value;
}

void ProgramState::nextLine()
{
	programCounter++;
}

int ProgramState::getCurrentLine() const
{
	return programCounter;
}

void ProgramState::setLine(int num)
{
	programCounter = num;
}

int ProgramState::maxLineNum() const
{
	return numLines;
}

void ProgramState::pushLine(int num)
{
	callStack.push(num);
}


bool ProgramState::canReturn() const
{
	return ! callStack.empty();
}

// This function assumes canReturn() -- the "right" way to do this 
// (from a programming point of view) is beyond what we've
// covered in CS 32 so far.
int ProgramState::returnLine()
{
	int top = callStack.top();
	callStack.pop();
	return top;
}

