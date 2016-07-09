
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool isinfixvalid(string infix);

int evaluate(string infix, string& postfix, bool& result);

bool evaluatepostfix(string infix, const string& postfix);

int main()
{
    string pf;
    bool answer;
    assert(evaluate("T| F", pf, answer) == 0  &&  pf == "TF|"  &&  answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&|"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cout << "Passed all tests" << endl;
    return 0;
}

bool isinfixvalid(string infix)
{
    int size = infix.size();
    int newsize = 0;
    string infixfixed;
    for (int i = 0; i < size; i++)
    {
        if (infix[i] != ' ')
        {
            infixfixed = infixfixed + infix[i];
            newsize++;
        }
    } // T F ! ( ) & |
    if (infix == "") //check empty string
    {
        return false;
    } //check ending
    if (infixfixed[newsize - 1] == '&' || infixfixed[newsize - 1] == '|' || infixfixed[newsize - 1] == '(' || infixfixed[newsize - 1] == '!')
    {
        return false;
    }
    int openingbracecount = 0; //check for same number of ( and )
    int closingbracecount = 0;
    for (int i = 0; i < newsize; i++)
    {
        if (infixfixed[i] == '(')
        {
            openingbracecount++;
        }
        if (infixfixed[i] == ')')
        {
            closingbracecount++;
        }
    }
    if (openingbracecount != closingbracecount)
    {
        return false;
    }
    for (int i = 0; i < newsize - 1; i++)
    {
        if (infixfixed[i] != 'T' && infixfixed[i] != 'F' && infixfixed[i] != '&' && infixfixed[i] != '|' && infixfixed[i] != '!' && infixfixed[i] != '(' && infixfixed[i] != ')')
        {
            return false;
        }
        if ((infixfixed[i] == 'T' || infixfixed[i] == 'F') && (infixfixed[i + 1] == 'T' || infixfixed[i + 1] == 'F' || infixfixed[i + 1] == '(' || infixfixed[i + 1] == '!'))
        {
            return false;
        }
        if (infixfixed[i] == '(' &&infixfixed[i + 1] == ')')
        {
          return false;
        }
        if (infixfixed[i] == ')' && infixfixed[i + 1] == '(')
        {
            return false;
        }
        if (infixfixed[i] == '!' && (infixfixed[i + 1] == '&' || infixfixed[i + 1] == '|'))
        {
            return false;
        }
        if (infixfixed[i] == '(' && (infixfixed[i + 1] == '&' || infixfixed[i + 1] == '|'))
        {
            return false;
        }
    }
    return true;
}

int evaluate(string infix, string& postfix, bool& result)
{
    if(!isinfixvalid(infix))
    {
        return 1;
    }
    postfix = "";
    stack<char> aStack;
    int size = infix.size();
    for (int i = 0; i < size; i++)
    {
        switch(infix[i])
        {
                case ' ':
            {
                break;
            }
                case 'F':
            {
                
            }
                case 'T':
            {
                postfix = postfix + infix[i];
                break;
            }
                case '(':
            {
                aStack.push(infix[i]);
                break;
            }
                case ')':
            {
                while (aStack.top() != '(')
                {
                    postfix = postfix + aStack.top();
                    aStack.pop();
                }
                aStack.pop();
                break;
            }
                case '&':
            {
                while (!aStack.empty() && aStack.top() != '(' && aStack.top() != '|')
                {
                    postfix = postfix + aStack.top();
                    aStack.pop();
                }
                aStack.push(infix[i]);
                break;
            }
                case '|':
            {
                while (!aStack.empty() && aStack.top() != '(' && aStack.top() != '&')
                {
                    postfix = postfix + aStack.top();
                    aStack.pop();
                }
                aStack.push(infix[i]);
                break;
            }
                case '!':
            {
                aStack.push(infix[i]);
                break;
            }
        }
    }
        while (!aStack.empty())
               {
                   postfix = postfix + aStack.top();
                   aStack.pop();
               }
    result = evaluatepostfix(infix, postfix);
    return 0;
}

bool evaluatepostfix(string infix, const string& postfix)
{
    int size = postfix.size();
    stack<bool> bStack;
    for (int i = 0; i < size; i++)
    {
        if (postfix[i] == 'T')
        {
            bStack.push(true);
        }
        if (postfix[i] == 'F')
        {
            bStack.push(false);
        }
        else if (postfix[i] == '&' || postfix[i] == '|')
        {
            bool operand2 = bStack.top();
         bStack.pop();
            bool operand1 = bStack.top();
         bStack.pop();
            bool realresult;
            if (postfix[i] == '&')
            {
                realresult = operand1 && operand2;
            }
            else
            {
                realresult = operand1 || operand2;
            }
            bStack.push(realresult);
        }
        else if (postfix[i] == '!')
        {
            if(bStack.top() == true)
            {
                bStack.top() = false;
            }
            else
            {
                bStack.top() = true;
            }
        }
    }
    if (bStack.top() == true)
    {
        return true;
    }
        return false;
}
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.)