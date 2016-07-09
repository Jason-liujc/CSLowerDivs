//
//  eval.cpp
//  Homework
//
//  Created by Jason on 7/13/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
using std::string;
using std::cout;
using std::stack;
bool balanced(std::string expr);

bool ifPaired(char a, char b);




int main() // hope you rename this something awesome.
{
    string test1="This class is CS 32 (Summer 2014)";
    
    if (balanced(test1))
        cout << "Test Sucess!";
    else
        cout << "Test Failed :(";
    
    
}


bool balanced(std::string expr)
{
    stack<char> Lebron;
    char currentChar; //for debuging purpose.
    int length=expr.size();
    string myStr1;
    char temp;
    bool truth;
    
    for(int i=0;i<length; i++) //err I have no idea why I wrote this. I guess I'll just leave it here.
    {
        
        if (expr[i]=='(' || expr[i]==')' || expr[i]=='{' || expr[i]=='}' || expr[i]=='[' || expr[i]==']')
            myStr1=myStr1+expr[i];
        
    }

    int size=myStr1.size();
    for (int i=0; i<size; i++)
    {
        truth=false; // set it false everytime.
        if (expr[i]=='(' || expr[i]=='{' || expr[i]=='[' ) //push in one side of the brackets
        {
            currentChar=expr[i];
            Lebron.push(expr[i]);
            
        }
        
        if ( expr[i]==')'|| expr[i]=='}' || expr[i]==']') //pop the other side
        {
            currentChar=expr[i];
            temp=Lebron.top();
            Lebron.pop();
            if (ifPaired(temp, expr[i]))
                truth=true;  //if paired we make it true.
            
            
            
        }
    }
    if (Lebron.size()!=0)
        return false;
    
    
    return truth;
}

bool ifPaired(char a, char b) //another function to check if they are paired, used by the main function.
{
    if (a=='(' && b==')')
        return true;
    if  (a=='{' && b=='}')
        return true;
    if (a=='[' && b==']')
        return true;
    return false;
    
    
    
}

