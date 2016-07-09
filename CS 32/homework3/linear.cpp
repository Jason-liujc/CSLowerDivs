
bool islower(char a){return (a>='a' && a<='z');}


// Return true if any of the chars in the array is lowercase, false
// otherwise.
bool anyLowercase(const char a[], int n)
{
    
    if (islower(a[n-1]))
        return true;
    
    if (n<1)
        return false;

    return anyLowercase(a, n-1);
    
    
}

// Return the number of lowercase chars in the array.
int countLowercase(const char a[], int n)
{
    //how many times???
    if (n<1)
        return 0;
        
    
    if (islower(a[n-1]))
    {
    
        return countLowercase(a, n-1)+1;
    
        
    }
    else
        return countLowercase(a, n-1);
    
}

// Return the subscript of the first lowercase char in the array.
// If no element is lowercase, return -1.
int firstLowercase(const char a[], int n)
{
    if (islower(a[0]))
		return 0;
    if (n == 0)
		return -1;
    if (firstLowercase(a+1, n-1)==-1)
        return -1;
    
	return 1 + firstLowercase(a+1, n-1);
    
}



// Return the subscript of the least char in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].)  If the array has no elements to examine, return -1.
int indexOfLeast(const char a[], int n)
{

    
    switch (n) {
        case 1:
            return 0;
            break;
            
        case 0:
            return -1;
        default:
            break;
    }
    
	if (a[0] <= a[n-1]) // to make sure it's the smallest/
		return indexOfLeast(a, n-1);
    
    
    else
    {
	return indexOfLeast(a+1, n-1)+1;
    }
    

}
    


