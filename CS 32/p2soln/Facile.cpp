// Facile.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "ProgramState.h"
#include "EndProgramStatement.h"
#include "AddStatement.h"
#include "SubStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "GotoStatement.h"
#include "IfStatement.h"
#include "GoSubStatement.h"
#include "ReturnStatement.h"
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>


using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

void interpretProgram(istream& inf, ostream& outf)
{
	vector<Statement *> program;
	parseProgram( inf, program );
	ProgramState * ps = new ProgramState( program.size() - 1 );
	int line ;
	while(true)
	{
		line = ps->getCurrentLine();
		program[line]->execute( ps, outf );
	}
}


int main()
{
        cout << "Enter Facile program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL); // or nullptr 
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	string type;
	char var;
	int val;

	ss << line;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal Facile program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable (single character) and then an integer value.
		statement = new LetStatement(var, val);
	}
	else if (type == "PRINT")
	{
		// remove from given.
		ss >> var;
		statement = new PrintStatement(var);
	}
	else if (type == "ADD")
	{
		ss >> var;
		ss >> val;
		statement = new AddStatement(var, val);	
	}
	else if (type == "SUB")
	{
		ss >> var;
		ss >> val;
		statement = new SubStatement(var, val);		
	}
	else if (type == "MULT")
	{
		ss >> var;
		ss >> val;
		statement = new MultStatement(var, val);		
	}
	else if (type == "DIV")
	{
		ss >> var;
		ss >> val;
		statement = new DivStatement(var, val);		
	}
	else if (type == "GOTO")
	{
		ss >> val;
		statement = new GotoStatement(val);
	}
	else if ( type == "IF")
	{
		string op, dummy;
		int comp;
		ss >> var >> op >> comp >> dummy >> val;
		statement = new IfStatement(var, op, comp, val);		
	}
	else if (type == "GOSUB")
	{
		ss >> val;
		statement = new GoSubStatement(val);
	}
	else if  (type == "RETURN")
	{
		statement = new ReturnStatement();
	}
	else if (type == "." || type == "END")
	{
		statement = new EndProgramStatement();
	}
		
	return statement;
}

