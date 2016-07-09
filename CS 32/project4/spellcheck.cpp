

#include <fstream>

#include <iomanip>

#include "hash.h"
#include<sstream>
#include<algorithm>

using namespace std;

const char		INFILE_NAME[] = "data.txt";
const char		INFILE_NAME2[] = "wordlist.txt";
const char		OUTFILE_NAME[] = "test.txt";


void spellCheck(istream& inf, istream& wordlistfile, ostream& outf);

void terminator(istream& inf, istream& wordlistfile, ostream& outf);
bool initializer(istream& inf, istream& wordlistfile, ostream& outf);


ifstream something1;
ifstream something2;
ofstream something3;




int main()
{
    


    initializer(something1, something2  , something3);  //open the file

    
    spellCheck(something1, something2  , something3);

    
    
    
    terminator(something1, something2  , something3); //close the file
    
}



bool myFunction(string a, string b)
{
    return b<a;
}


bool contains(vector<string> words, string value) //to make sure there's no repeated items.
{
    return (find(words.begin(), words.end(), value) != words.end());
       
}


void spellCheck(istream& inf, istream& wordlistfile, ostream& outf)
{
    //file 1: contain the word we want to exaime.
    //file 2: contain the words we use to examine.
    //file 3: the output file/
    vector<bool> exist;
    bool found=true;
    
    
    HashTable dictionary;
    
    
    //to get the word by word from file 1.
    string word;
    list<string>lines;
    list<string>lines2;

    
    string c;
    vector<string> words;
    vector<string> suggestion;
    vector<string> badwords;
    vector<string> original;
    list<int> linenum;
    list<int> linesnum2;
    
    while(!inf.eof())
    {
        getline(inf, c);
        
        lines.push_back(c); //for examing issue
        lines2.push_back(c); //for printing issue.
        
    }
    
   
  
    
    
    
    string temp;
    
    int counter=1;
    while(!lines.empty())
    {
        stringstream stream(lines.front());
        while(stream>>temp)
        {
        
            linenum.push_back(counter);
            
        }
        lines.pop_front();
        counter++;
        
        
    }
        
    inf.clear();
    inf.seekg(0, ios::beg);  //reset the get method to it's starting point.
    
    string worda;
    while (inf >> word)
    {
        
        original.push_back(word);
        
        for (int i=0; i<word.length(); i++)
        {
            if(isalpha(word[i]))
                worda=worda+string(1,tolower(word[i]));
        }
        if(worda=="i") //special case.
            worda="I";
        
        
        words.push_back(worda);
        
        worda="";
    }
    
 
    
    string sample;
    while(wordlistfile >> sample)
    {
         dictionary.insert(sample);
    }
    string check, check2;
    int currentnum=1;
    
    list<string>::iterator ll=lines2.begin();
    
   
    string currentLine=*ll;
    
    
    vector<string>::iterator j=words.begin();
    vector<string>::iterator j2=original.begin();
    
    while (j!=words.end())
    {
        
        
        if(currentnum<linenum.front())///a new line
            ll++;
        
        currentLine=*ll;
        
        currentnum=linenum.front();
        
        
        
        check=*j;
        check2=*j2; //for the original word.
        
        if (!dictionary.exist(check))
        {
            outf <<currentLine<<endl;
            
            badwords.push_back(check2);
           
            found=false;
            
            //swaping
            for (int i=0; i<check.size();i++)
            {
                string temp=check;
                swap(temp[i], temp[i+1]);
                
                if(dictionary.exist(temp) && !contains(suggestion, temp))
                   suggestion.push_back(temp);
                
                
            }
            
            
            //insert in adjacent.
            for (int i=0; i<check.size();i++)
            {
                
                
                string temp=check;
                
                for (int k=0; k<26; k++)
                {
                    string temp2=string(1,'a'+k);
                    temp.insert(i,temp2);
                    
                    if(dictionary.exist(temp)&& !contains(suggestion, temp))
                        suggestion.push_back(temp);
                    temp=check;

                }
                
                
            }
            
            //erase one char
            
            for(int i=0; i<check.size();i++)
            {
                string temp=check;
                temp.erase(temp.begin()+i);
                
                
                if(dictionary.exist(temp)&& !contains(suggestion, temp))
                    suggestion.push_back(temp);
                
                
            }
            
            
            //replacing character
        
            for (int i=0; i<check.size();i++)
            {
                
                string temp=check;
                
                for (int k=0; k<26; k++)
                {
                    string temp2=string(1,'a'+k);
                    temp.replace(i, 1, temp2);
                    if(dictionary.exist(temp)&& !contains(suggestion, temp))
                        suggestion.push_back(temp);
                    
                    
                }
                
                
            }
        
            
            //splitting words
            
            
            for (int i=1; i<check.size();i++)
            {
                int end=(int)check.length()-1;
                string temp1=check.substr(0,i);
                
                string temp2=check.substr(i,end);
                
                if(dictionary.exist(temp1)&& dictionary.exist(temp2))
                    suggestion.push_back(temp1+" "+temp2);
               
                
                
            }
            
            //here's the part we sort the suggestion.
            //not quite!!!
            vector<string>::iterator ite=suggestion.begin();
            vector<string>::iterator ite2=suggestion.end();
            
            sort(ite,ite2,myFunction);
            
            
            
            
            suggestion.push_back(" "); //to mark it so that we know its different words
            
            
            
        }
        
        
        
        
        string badtemp;
        while(!badwords.empty())
        {
           //
            //cout << c<<endl;
            
            

            suggestion.pop_back();
            
             badtemp=badwords.back();
            for(int k=0; k<badtemp.length();k++)
            {
                badtemp[k]=toupper(badtemp[k]);
            }
            
            
            outf << "word not found: " << badtemp << endl;
            outf << "perhaps you meant: " << endl;
            string temp;
            
            while(suggestion.back()!=" " && !suggestion.empty())
            {
                temp=suggestion.back();
                for (int i=0; i<temp.length(); i++) {
                    temp[i]=toupper(temp[i]);
                }
                
                
                outf << temp << endl;
                suggestion.pop_back();
                
                
                
                
            }
            
            
            badwords.pop_back();
            
          
            outf<< endl;
            
            
        }
        
        linenum.pop_front();
        
        j++;
        j2++;

        
    }
    
    
    
}


void terminator(istream& inf, istream& wordlistfile, ostream& outf)
{
    
    if (wordlistfile)
    {
        // Close the input file
        something2.close();
    }
    
    
    // If there is an input file open
    if (inf)
    {
        // Close the input file
        something1.close();
    }
    
    // If there is an output file open
    if (outf)
    {
        // Close the output file
        something3.close();
    }
    
}


bool initializer(istream& inf, istream& wordlistfile, ostream& outf)
{
    
    
    something2.open(INFILE_NAME2);
    something1.open(INFILE_NAME);
    something3.open(OUTFILE_NAME);
    
    
    if ( ! wordlistfile )
    {
        cerr << "Error: Cannot open wordlistfile.txt!" << endl;
        return false;
    }
    
    
    if ( ! inf )		        // Did opening the file fail?
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    
    
    
    if ( ! outf )
    {
        cerr << "Error: Cannot create test.txt!" << endl;
        return false;
    }
    return true;
    
}