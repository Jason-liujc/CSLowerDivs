#include "graphlib.h"
#include <iostream>
#include <cctype>
#include <cassert>
#include <string>

using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int BG = 0;
const int FG = 1;
const int middle = NCOLS / 2;
 bool plotLine (int r, int c, int dir, int distance, char plotChar, int fgbg); //Mention this boolean function first
int executeCommands(string commandString, char& plotChar, int& mode, int& badPos); // Mention this function first
bool validCommand(string commandString);
bool isValid=true;
bool isValidFirstChar(string commandString, int& i);
 bool anyExecutionError=true;

// cout << plotLine(3, 5, HORIZ, 2, '@', FG) <<endl; --test code
//int bp;
//int m = FG;
//char pc = '@';
//executeCommands("H2", pc, m, bp);
//draw();
int main()
{
    
    clearGrid();
    

    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = executeCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot execute command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "executeCommands returned " << status << "!" << endl;
        }
    }
}

 bool plotLine (int r, int c, int dir, int distance, char plotChar, int fgbg)
{
    
    if (dir ==0 || dir ==1)  //make sure all the conditions are satisfied
    {
        if (fgbg==0 || fgbg ==1)
        {
            if (isprint(plotChar))
            {
                if (r<20 || c<30)
                {
                    if (fgbg==1) // The case when we plot foreground
                    {
                        
                        
                        switch (dir)
                        {
                            case 0:
                                if (distance >= 0)  //Distance is larger than zero
                                {
                                    for (int k=1;k<=distance+1;k++)  //plot horizontal line
                                    {
                                        setChar(r, c, plotChar);
                                        c++;
                                        
                                        
                                    }
                                    
                                    return true;
                                }
                                
                                else //distance is smaller than zero
                                {
                                    distance=abs(distance);
                                    
                                    for (int k=1;k<=distance+1;k++)  //plot horizontal line
                                    {
                                        setChar(r, c, plotChar);
                                        c--;
                                        
                                        
                                    }
                                    return true;
                                }
                                break; // I don't think I need a break, but I'll put it here anyway.
                            case 1:
                                
                                if (distance >= 0)  //Distance is larger than zero
                                {
                                    for (int k=1;k<=distance+1;k++)  //plot vertical line
                                    {
                                        setChar(r, c, plotChar);
                                        r++;
                                        
                                        
                                    }
                                    
                                    return true;
                                }
                                
                                else //distance is smaller than zero
                                {
                                    distance=abs(distance);
                                    
                                    for (int k=1;k<=distance+1;k++)  //plot plot vertical line
                                    {
                                        setChar(r, c, plotChar);
                                        r--;
                                        
                                        
                                    }
                                    return true;
                                }
                                break; // I don't think I need a break, but I'll put it here anyway.
                                
                                
                                
                                return true;
                        }
                    }
                    if (fgbg==0) // The case when we plot background
                    {
                        
                        switch (dir)
                        {
                            case 0:
                                if (distance >= 0)  //Distance is larger than zero
                                {
                                    for (int k=1;k<=distance+1;k++)  //plot horizontal line
                                    {
                                        if (getChar(r,c)==' ')
                                        {
                                            
                                            setChar(r, c, plotChar);
                                        }
                                        c++;
                                        
                                    }
                                    
                                    return true;
                                }
                                
                                else //distance is smaller than zero
                                {
                                    distance=abs(distance);
                                    
                                    for (int k=1;k<=distance+1;k++)  //plot horizontal line
                                    {
                                        if (getChar(r, c)==' ')
                                        {
                                            setChar(r, c, plotChar);
                                        }
                                        c--;
                                        
                                        
                                    }
                                    return true;
                                }
                                break; // I don't think I need a break, but I'll put it here anyway.
                            case 1:
                                
                                if (distance >= 0)  //Distance is larger than zero
                                {
                                    for (int k=1;k<=distance+1;k++)  //plot vertical line
                                    {
                                        if (getChar(r,c)==' ')
                                        {
                                            
                                            setChar(r, c, plotChar);
                                        }
                                        r++;
                                        
                                        
                                    }
                                    
                                    return true;
                                }
                                
                                else //distance is smaller than zero
                                {
                                    distance=abs(distance);
                                    
                                    for (int k=1;k<=distance+1;k++)  //plot plot vertical line
                                    {
                                        if (getChar(r,c)==' ')
                                        {
                                            
                                            setChar(r, c, plotChar);
                                        }
                                        r--;
                                        
                                        
                                    }
                                    return true;
                                }
                                break; // I don't think I need a break, but I'll put it here anyway.
                                
                                
                                
                                return true;
                        }
                        
                        
                        }
                    return false; //it shouldn't be possible to get to this statement
                    
                    }
                
                    return false;
                
            }
            
                return false;
            
        }
        
            return false;
        
        
    }
   
    
    
    return false;
}

int executeCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
   
    int length=commandString.size();
    int r1=1;   //current position
    int c1=1;
    int dir1,distance1,fgbg1;
    //char currentChar = '*';
    //int currentMode = FG;
    
    
    for (int i=0; i<commandString.size(); i++) // check whether the command is valid or not. The reason I did another for-loop              is to make this thing more clear.
    {
        if (toupper(commandString[i-1])=='H' || toupper(commandString[i-1])=='V')
        {
        if (commandString[i]=='+')
        {
            if (isValid==true)
            {
                badPos=i;
            }
            else
            {
                if (badPos>i)// make sure it's the far lefiest
                {
                    badPos=i;
                }
            }
            isValid=false;
        }
        }
    }
    
    for (int i=0; i<commandString.size(); i++)
    {
        if (toupper(commandString[i-1])=='H' && commandString[i]=='-') // should be lower case as well
        {
            if (isdigit(commandString[i+1]))
                break;
            else
                
            {
                
            
            if (isValid==true)
            {
                badPos=i-1;
            }
            else
            {
                if (badPos>i)// make sure it's the far lefiest
                {
                    badPos=i-1;
                }
            }
                isValid=false; }
        }
    }
    
    for (int i=0; i<commandString.size(); i++) // take care of the "VB" cases
    {
        
        if (toupper(commandString[i-1])=='V' && isdigit(commandString[i])==false)
        {
            if (commandString[i]=='-')
                break;
            if (isValid==true)
            {
                badPos=i-1;
            }
            else
            {
                if (badPos>i)// make sure it's the far lefiest
                {
                    badPos=i-1;
                }
            }
            isValid=false;
        }
        
    }
    
    for (int i=0; i<commandString.size(); i++)  // take care of the C1 cases
    {
        if (toupper(commandString[i-1])=='C' && isdigit(commandString[i]))
        {
            if (isValid==true)
            {
                badPos=i;
            }
            else
            {
                if (badPos>i)// make sure it's the far lefiest
                {
                    badPos=i;
                }
            }
            isValid=false;
            
        }
        if (toupper(commandString[i-1])=='C' && commandString[i]=='-')
        {
            if (isValid==true)
            {
                badPos=i;
            }
            else
            {
                if (badPos>i)// make sure it's the far lefiest
                {
                    badPos=i;
                }
            }
            isValid=false;
            
        }
      
        
        
        if (commandString[i]==' ') // take care of space after valid first command chars.
        {
           if (toupper(commandString[i-1])!='B' && toupper(commandString[i-1])!='V' && toupper(commandString[i-1])!='H' && toupper(commandString[i-1])!='F' && toupper(commandString[i-1])!='C')
           {
               
               if (isValid==true)
               {
                   badPos=i;
               }
               else
               {
                   if (badPos>i)// make sure it's the far lefiest
                   {
                       badPos=i;
                       
                   }
               }
               isValid=false;
               
               
               
           }
            
            
        }
        
        if (commandString[i]=='H' || commandString[i]=='V') // take care of BH1 cases.
        {
            if (commandString[i-1]=='F' || commandString[i-1]=='B')
            {
                if (isdigit(commandString[i+1]))
                {
                    
                    if (isValid==true)
                    {
                        badPos=i+1;
                    }
                    else
                    {
                        if (badPos>i+1)// make sure it's the far lefiest
                        {
                            badPos=i+1;
                            
                        }
                    }
                    isValid=false;
                    

                    
                    
                }
                
            }
            
        }
        if (commandString[i-1]=='-') // -1- cases
        {
            if(isdigit(commandString[i]))
            {
                if (commandString[i+1]=='-')
                    {
                        
                        if (isValid==true)
                        {
                            badPos=i+1;
                        }
                        else
                        {
                            if (badPos>i+1)// make sure it's the far lefiest
                            {
                                badPos=i+1;
                                
                            }
                        }
                        isValid=false;
                        
                        
                    }
                
                
            }
        }
        
      
    }
    
    for (int i=0; i<commandString.size(); i++)
    {
        
        if (isalnum(commandString[i])==false)
        {
            if (commandString[i]=='-')
                break;
            if (toupper(commandString[i-1])!='F' && toupper(commandString[i-1])!='B')
            {
                
                if (isValid==true)
                {
                    badPos=i;
                }
                else
                {
                    if (badPos>i)// make sure it's the far lefiest
                    {
                        badPos=i;
                    }
                }
                isValid=false;
            }
            
        }
        if (commandString[i]=='-')  //take account for H--
        {
            if (commandString[i-1]=='-')
            {
                if (isValid==true)
                {
                    badPos=i;
                }
                else
                {
                    if (badPos>i)// make sure it's the far lefiest
                    {
                        badPos=i;
                    }
                }
                isValid=false;

            }
        }
    }
    
    
    
        
        
    
    if (toupper(commandString[length-1])=='H' || toupper(commandString[length-1])=='V')  //exclude the condition where H or V is the last one.
    {
        if (toupper(commandString[length-2])!='B' && toupper(commandString[length-2])!='F')
        {
            if (isValid==true)
            {
                badPos=length;
            }
            else
            {
                if (badPos>length)// make sure it's the far lefiest
                {
                    badPos=length;
                }
            }
            isValid=false;

            
            
        }
    }
    if (toupper(commandString[0])!='B' && toupper(commandString[0])!='V' && toupper(commandString[0])!='H' && toupper(commandString[0])!='F' && toupper(commandString[0])!='C') // makes sure the frst string is valid
    {
        badPos=0;
        isValid=false;
        
        
    }
    
    
    
    
    //Now start the plotting stuff
    for (int i=0; i<commandString.size();i++)
    {
        
        
        if (toupper(commandString[i-1])=='H')   //plot horizontal line
        {
           
            
            dir1=0;
           distance1=atoi(&commandString[i]);  //convert the string to integer type.
          
            if ((c1+distance1)>30)   //check for out of bounds
            {
                if (i-1>badPos)      //Need to double check this.
                    break;
                badPos=i-1;
                return 2;
            }
            
            if ((r1+distance1-1)<0)  //check for out of bounds
            {
                if (i-1>badPos)
                    break;
                badPos=i-1;
                return 2;
            }
            
          if (isValid==true)
            plotLine(r1, c1, dir1, distance1, plotChar  , mode);
            
            
            c1=c1+distance1;  //remember the current location.
            
        }
        
        
        
        if (toupper(commandString[i-1])=='V')
        {
            dir1=1;
            distance1=atoi(&commandString[i]);
            
            
            if ((r1+distance1)>20)  //check for out of bounds
            {
                if (i-1>badPos)
                    break;
                badPos=i-1;
                return 2;
            }
            
            if ((r1+distance1-1)<0)  //check for out of bounds
            {
                if (i-1>badPos)
                    break;
                badPos=i-1;
                return 2;
            }
              if (isValid==true)
            plotLine(r1, c1, dir1, distance1, plotChar, mode);
            
            r1=r1+distance1; //remember the current location.
        }
        
        
        
        if (toupper(commandString[i-1])=='F')
        {
            
            plotChar=(char)commandString[i];
            mode=FG;
            
        }
        
        if (toupper(commandString[i-1])=='B')
        {
          
            plotChar=(char)commandString[i];
            mode=BG;
            
        }
        
        
        if (toupper(commandString[i])=='C')
        {
            clearGrid();
        }
        
        
        
        
        
        
    }
    
    
    if (isValid==false)  //make sure it returns false when there's a syntax error in the command string.
        return 1;
    else if (isValid==true)
        return 0;
   
    else
        return 3;
}
