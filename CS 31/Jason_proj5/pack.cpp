//things worth noticing:
//two #P# is treated as one.
//if the word is too ong, the rest of that word portion goes to the next line.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

const char		INFILE_NAME[] = "results.txt";
const char		OUTFILE_NAME[] = "test.txt";


int pack(int lineLength, istream& inf, ostream& outf);
bool initializer(istream& inf, ostream& outf);
void terminator(istream& inf, ostream& outf);


void processArr1(char a[], int counter);
void processArr2(char a[], int counter, int counter2);
void print (ostream &outf, int counter3, char b[], int maxLength, int &number, int linelength);


ifstream infile;
ofstream outfile;
bool isStart=false;
bool isEnd=false;



int main()
{
 
  
    int MAX;
    cin >> MAX;
    initializer(infile, outfile);
    pack(MAX, infile, outfile);
   
    
    terminator(infile,outfile);
    
    
    
    
}
int pack(int lineLength, istream& inf, ostream& outf)
{
    
    if (lineLength<1)
        return 2;
   
    
    int counter=0;  //counter for character numebrs.
   
    char c;
    
	while(1)   //count the number of characters here
    {
        if(infile.peek() == -1)
            break;
        c = infile.get();
        if(c != infile.eof())
            counter++;
    }
    
  
    // The getline function doesn't work for my compiler, so this is the only solution I can think of.
    
    infile.clear();
    infile.seekg(0, ios::beg);  //reset the get method to it's starting point.
    
    
    
    
    char a[counter];
    
    
    
    //put the character on a string called a[].
    
     int i=0;
    while (infile.get(c))
    {
        a[i]=c;
        i++;
        
    }
    
    //now the manipulation of the array part.
    
    processArr1(a, counter);    //multiple functions is to make sure the process of this char array is complete.
    processArr1(a, counter);
    
                                // count how many space is need.
    
    
    int counter2=0;             //count how many symbols of '.', '!' or '?'
    int k=0;
    
    while (k<counter)
    {
        if(a[k]=='.' || a[k]=='!' || a[k]=='?')
            counter2++;
        k++;
    }
    
    int counter3=counter+counter2;
    k=0;
    char b[counter3];   //add another char array b for extra spaces.
    while (k<counter3)
    {
        if(k<counter)
        {
            b[k]=a[k];
            
            k++;
        }
        
        else
        {
            b[k]=a[counter-1];    //put the rest of b as the last charactor of a.
            k++;
        }
        
    }
    

    
    //now the array b is what we are looking at.
    
    processArr2(b, counter, counter3);
    
    
    
    //now the output the char array onto the file.
    
    
  
    int number; //number to return.
    
    
   print (outfile,counter3, b, lineLength, number, lineLength);
    
    
    
    
    
    
 
    return number;
    
}





bool initializer(istream& inf, ostream& outf)
{
    infile.open(INFILE_NAME);
    
    outfile.open(OUTFILE_NAME);
    
    
    
    
    if ( ! outfile )
    {
        cerr << "Error: Cannot create greeting.txt!" << endl;
        return false;
    }
    
    if ( ! infile )		        // Did opening the file fail?
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    return true;
    
}


void terminator(istream& inf, ostream& outf)
{
    
    
    
    // If there is an input file open
    if (infile)
    {
        // Close the input file
        infile.close();
    }
    
    // If there is an output file open
    if (outfile)
    {
        // Close the output file
        outfile.close();
    }
    
}


void processArr1(char a[], int counter)   //make sure that there's no extra lines or spaces.
{
 
    if (a[counter-1]=='\n')
    {
        a[counter-1]='.';
    }
    
    
    for (int i=0; i<counter; i++)   //get rid of the extra spaces in the infile text.
    {
        for (;;)
        {
            if (a[i]==' ' && a[i+1] ==' ')
            {
                for (int k =i+1; k <= counter-1; k++)
                {
                    a[k-1] = a[k];
                    
                    
                    
                }
                
            }
            
            
            
            else if (a[i]=='\n')  //get rid of the extra lines in the infile text.
            {
                for (int k =i+1; k <= counter-1; k++)
                {
                    
                    a[i]=' ';
                    
                    
                    
                }
                
            }
            

            
            else
            {
                break;
            }
            
            
        }
        
        
        
        
    }
    
    if (a[counter-1]=='\n')
    {
        a[counter-1]='.';
        
    }
    
    
}


//not sure if this function is useful.
void processArr2(char a[], int counter, int counter2)  //add a space after every '.', '?' and '!'.
{
    
    
    
    for (int i=0; i<counter; i++)
    {
        
        if (isalnum(a[i-1]) && isalnum(a[i+1]) &&a[i]=='.') // in case there is a dot in the middle.
            continue;
        
        if (a[i]=='.' || a[i]=='!' || a[i]=='?' )  //get rid of the extra lines in the infile text.
        {
            
            
            for (int k =counter2-1; k >=i+1; k--)
            {
                
                a[k]=a[k-1];
                
            }
            
            
            
            a[i+1]=' ';
        
        }
    }

}


void print (ostream &outf, int counter3, char b[], int maxLength, int &number, int linelength)
{
    bool isStart=false;
    bool isEnd=false;
    int currentLength=0;
    int wordLength=0;;
    int m=0;  //another counter
    int stored=0;
    int stored2=0;
    int j=0;
    bool hasSpace=false;
    
    number=0;
    while (j<counter3)
        
        
    {
        //take care of extra '.' and ' ' at the end of the string
        
        if (b[j]=='.' && b[j+1]==' ' && b[j+2]=='.')
        {
            outf << b[j];
            break;
        }
        if (b[j]=='?' && b[j+1]==' ' && b[j+2]=='?')
        {
            outf << b[j];
            break;
        }
        if (b[j]=='!' && b[j+1]==' ' && b[j+2]=='!')
        {
            outf << b[j];
            break;
        }
        if (b[j]=='.' && b[j+1]==' ' && b[j+2]=='#' && b[j+3]=='P' && b[j+4]=='#')
        {
            outf << b[j]<<b[j+2]<<b[j+3]<<b[j+4];
            break;
        }
        
      
        
        //take account of when the thing starts with #P#.
        
      
        
        if (b[j]=='#' && b[j+1]=='P'&& b[j+2]=='#' && j==0)
        {
            
            
            isStart=true;
        }
        if (j>5)  //in case the #P# is in the end. 
        {
            if (b[j]=='#' && b[j+1]=='P'&& b[j+2]=='#' && j>counter3-20)
            {
                
                
                isEnd=true;
            }
        }
        
     //take care of the #P# case
        if (b[j]=='#' && b[j+1]=='P' && b[j+2]=='#' && j!=0&& isStart==false && isEnd==false)  //how to do multiple ones?
        {
            
            while (b[j+3]=='#' && b[j+4]=='P' && b[j+5]=='#')  //in case there are multiple #P#s
            {
                j=j+3;
            
                
            }
            
            j=j+4;
            
            outf << endl << endl;
            currentLength=0;
            
            
                
            
        }
        
        else if (isalnum(b[j]) && b[j]!='P')
        {
            isStart=false;
        }
        
        
        //count the length of the next word.
        
        m=j;
        while(b[m]!=' ' && b[m]!='.' && b[m]!='-'  && b[m]!='!'  && b[m]!='?'  && b[m]!=',' && b[m]!=';' && b[m]!=':')
        {
            wordLength++;
            
            
            m++;
            if(b[m]==' ')  //in case it's a the end of the line.
                hasSpace=true;
            else
            {
                hasSpace=false;
            }
            
            
        }
        
        if (hasSpace==true)
        {
        
            if (wordLength>linelength)
            {
                number=1;
                
            }
        }
        
        
        stored=wordLength+1;
        stored2=wordLength; //in case the last word of the sentence is exceeding the current length with a spaec, this variable will cancel the space.
            
        wordLength=0;
        
        if(currentLength+stored<=maxLength) // if it fits, we are good and print the char
        {
           
            
            outf << b[j];
            currentLength++;
           
        }
      else if (currentLength+stored>maxLength && currentLength+stored2<=maxLength && hasSpace==true) // in case there's a space in the end.
      {
          
          outf << b[j];
          currentLength++;
      }
        
        else if (stored>maxLength) //in case the word is longer than the maxlength
        {
            outf << endl;
            currentLength=0;
            while (stored>0)
            {
                outf << b[j];
                currentLength++;
                j++;
                stored--;
                if (currentLength==maxLength)
                {
                    outf << endl;
                currentLength=0;
                }
                
            }
            j--;
        }
        
        
        else   // if it maxes out, we need a new line.
        {
            
            
            outf << endl;
            currentLength=0;
            
            if (currentLength==0 && b[j]==' ')
            {
                
                if (b[j+1]==' ')
                    j++;
                j++;
                
                
            }

            outf <<b[j];
            currentLength++;
        }
        
        j++;
        
    }
    
}





