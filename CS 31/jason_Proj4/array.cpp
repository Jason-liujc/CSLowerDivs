#include <iostream>
#include <string>
#include <assert.h>


using namespace std;  // ***remember to write reasons for test case in report***


int findLast(const string a[], int n, string target);
int tally(const string a[], int n, string target);
bool findFirstSequence(const string a[], int n, string target, int& begin, int& end);
int moveToEnd(string a[], int n, int pos);
int moveToBeginning(string a[], int n, int pos);
int disagree(const string a1[], int n1, const string a2[], int n2);
int removeDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
int mingle(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int divide(string a[], int n, string divider);

int positionOfMin(const string a[], int n);

int main ()
{

    string h[7] = { "peter", "lois", "meg", "chris", "", "meg", "stewie" };
    assert(tally(h, 7, "meg") == 2); // test whether it functions normally.
    assert(tally(h, 7, "") == 1);  // to see if it recognize empty string.
    assert(tally(h, 7, "quagmire") == 0); // test whether it functions well if the string is not in the array.
    assert(tally(h, -10, "quagmire") == -1); // test whether it outputs -1 when the n is negnative.
    assert(tally(h, 4, "")==0); // it's in the string but it not within the n range.
    assert(tally(h, 0, "meg") == 0); //test what does it do when n is zero.
    assert(findLast(h, 7, "meg") == 5); // a successful case for findLast function.
    assert(findLast(h, 2, "meg") == -1); // what if the function can't find the designated string?
    assert(findLast(h, -2, "meg") == -1); //to see the function returns -1 if n is negative.
    int bg;
    int en;
    assert(findFirstSequence(h, 7, "chris", bg, en) && bg == 3 && en == 3); // test whether it works normally.
    string test[10]={"peter" , "lois", "meg", "chris", "", "meg", "stewie", "lois" , "lois"};
    assert(findFirstSequence(test, 12, "lois", bg, en) && bg == 1 && en == 1);  //test whether it only takes the earileset set.
    assert(findFirstSequence(test, -12, "lois", bg, en)==false); // test what happens when
    assert(findFirstSequence(test, -12, "nobody", bg, en)==false); // test what if the name is not in the string array.
    
    
    string g[4] = { "peter", "lois", "chris", "stewie" };
    assert(positionOfMin(g, 4) == 2);  // check the position of a string.
    assert(positionOfMin(g, -1) == -1); // what if n is negative.
    assert(positionOfMin(g, 0) == -1); //what if the arrary have no elements.
    
    assert(disagree(h, 4, g, 4) == 2); //test if it works normally.
     assert(disagree(h, 4, g, 1) == 1); //test what if one of them is really short.
    
    string family[5] = { "peter", "lois", "meg", "chris", "stewie" };
    string people[6] = { "peter", "lois", "quagmire", "cleveland" };
    assert(disagree(family, 5, people, 4)==2); //test if it works normally.
    assert(disagree(family, 2, people, 1)==1);//test what if one of them is really short.
    assert(subsequence(h, 7, g, 4)); //this tests good
    assert(moveToEnd(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "lois"); // check if it works normally.
	
    string f[4] = { "chris", "stewie", "meg", "lois" };
    assert(moveToBeginning(f, 4, 2) == 2 && f[0] == "meg" && f[2] == "stewie"); // this works, as one can see in my report, I tested a lot of this cases
	
    string e[5] = { "chris", "chris", "chris", "meg", "meg" };
    assert(removeDups(e, 5) == 2 && e[1] == "meg");// test if this function works.
	
    string x[4] = { "brian", "lois", "lois", "quagmire" };
    string y[4] = { "chris", "lois", "meg", "stewie" };
    string z[10];
    assert(mingle(x, 4, y, 4, z, 10) == 8 && z[5] == "meg"); //mingle is kind of weird in my program.
	
    assert(divide(h, 7, "meg") == 3); // test if this function works.
    assert(divide(x, 4, "lois")==1); // what if there are multiple lois.
	
    cout << "All tests succeeded" << endl << endl;
    
    
    }
    


int findLast(const string a[], int n, string target)
{
    int counter=0;;
    if (n<0)
        return -1;
    
    for (int i=0; i<n; i++)
    {
        if (a[i]==target)
            counter=i;
    }
    
    if (counter==0)  //if there are no such string.
        return -1;
    
    
    return counter;
    
    
    
}

int tally(const string a[], int n, string target)
{
    int counter=0;
    if (n<0)
        return -1;
    for (int i=0; i<n; i++)
    {
        if (a[i]==target)
            counter++;
        
        
        
    }
    return counter;
    
}

bool findFirstSequence(const string a[], int n, string target, int& begin, int& end)
{
    int counter=0;
    
    
    if (n<0)
        return false;
    
    
    for (int i=0; i<n; i++)
    {
        if (a[i]==target)
        {
            begin=i;
            for (int k=i;k<n;k++)
            {
                if (a[k]==target)
                    counter++;
                end=begin+counter-1;
                if (a[k]!=target)
                    return true;
                
            }
            
        }
        
        
    }
    
    
    if (begin==0)
        return false;
    
    return true;
    
    
}




int disagree(const string a1[], int n1, const string a2[], int n2) // I changed the meaning of n in this one
{
    int counter=0;
    if (n1<0)
        return -1;
    if (n2<0)
        return -1;
    
    if (n1<=n2)
    {
        for (int i=0; i<n1 ; i++)
        {
            if (a1[i]==a2[i])
            {
                counter++;
            }
            else
                break;
        }
        
    }
    else
    {
        for (int i=0; i<n2 ; i++)
        {
            if (a1[i]==a2[i])
            {
                counter++;
            }
            else
                break;
        }
        
        
        
    }
    return counter;
}

int removeDups(string a[], int n) // undeveloped
{
    
    int counter=0;
    //now find out what number to return:
    int timer=0;
    
    while (timer<n)
    {
      
        if (a[timer]==a[timer+1])
        {
            
            counter++;   // counts how many duplicates are there.
        }
        timer++;
    }
    
    
    
    if (n<0)   //if n is negative
        return -1;
    for (int k=0; k<n ; k++)
    {
        for (int i=0; i<n; i++)
        {
            if (a[i]==a[i+1])
            {
                
            
                moveToEnd(a, n, i);   //move all the unwanted/duplicates to the back.
                
            }
            
        }
    }
return n-counter;
    
    
}



bool subsequence(const string a1[], int n1, const string a2[], int n2)

{
    
    int stored1=-1;   // because I want the starting point to be negative so that the if (stored1>=stored2) return false if the stored one have changed.
    int stored2=0;
    if (n1<0)
        return false;
    if (n2<0)
        return false;
    
    for (int i=0; i<n2; i++)
    {
        for (int k=stored1+1; k<n1; k++)
        {
            if (a2[i]==a1[k])
            {
                stored1=k;
                break;
            }
            
            
            
                
        
            
            
        }
        
        if (stored1>=stored2)   // find the largest stored value (k)
        {
        stored2=stored1; //put stored2 as the maximum value for k
        }
        else
        {
            return false;
        }
        
    }
    return true;
    
    
}

int mingle(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    if (n1<0)
        return false;
    if (n2<0)
        return false;     // test n so that it is not negative.
    if (n1+n2>max)
        return false;
    int k=0, m=0, n=0;
    //if not decreasing order, it's wrong as well.
   
    for (int i=0; i<n1-1; i++)
    {
        if (a1[i]>a1[i+1])
        {
            return false;
        }
    }
    for (int i=0; i<n2-1; i++)
    {
        if (a2[i]>a2[i+1])
        {
            return false;
        }
    }
    
    // actually mingle them together
    while(n<(n1+n2-1))
    {
        if(a1[k]<=a2[m])
        {
            
            result[n]=a1[k];
          
            k++;
            n++;
            
            if (n==n1+n2)  // what if there is one last element left.
            {
                if (m<n2)   
                n--;
            }
          
        }
        if (a1[k]>a2[m])
        {
            
            
            
            result[n]=a2[m];
            
            m++;
            n++;
            
            
            
        }
        
    }
    
    return n1+n2;
}



int moveToEnd(string a[], int n, int pos) // move the designated string one place to the end, and let other fullfill it.
{
    if (n<0)
        return -1;
	string movingString = a[pos]; //stores the element that will be moved
    
	int k = pos;
	while (k < n-1)
	{
		a[k] = a[k+1];
		k++;
	}
	a[n-1] = movingString; //put the string into the position we want.
	return pos;
}

int moveToBeginning(string a[], int n, int pos) //same as above except moves value at pos to front
{
    if (n<0)
        return -1;
	string movingString = a[pos]; //stores the element that will be moved
    
	int k = pos;
	while (k > 0)
	{
		a[k] = a[k-1];
		k--;
	}
	a[0] = movingString;
	return pos;
}



int divide(string a[], int n, string divider)

{
    if (n<0)
        return -1;
    
    
	int counter = 0;
	for (int k = 0; k < n; k++)//this moves all values less than divider to the front
	{
		if (a[k] < divider)
		{
			moveToBeginning(a, n, k); //calls the oneStepLeft function
			counter++;
		}
	}
	for (int k = n-1; k >= 0; k--) //this moves all values greater than divider to the end
	{
		if (a[k] > divider)
			moveToEnd(a, n, k); //calls the oneStepRight function
	}
    
	if (counter != 0)
		return counter;
	return n; //returns n if there were none
}



int positionOfMin(const string a[], int n) // returns -1 if there is no such string
{
	if (n <= 0) //check that n is positive, if there is zero element, it's zero as well (the array has no elements)
		return -1;
	string lowestString = a[0];
	int lowestStringNum = 0;
    
	for (int k = 0; k < n; k++)
	{
		if (a[k] < lowestString)
		{
			lowestString = a[k]; //if the current string is the lowest, sets it to the value and sets the int to its position
			lowestStringNum = k;
		}
	}
	return lowestStringNum; //returns the positon of the string
}









