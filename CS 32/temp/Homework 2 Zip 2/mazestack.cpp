

#include <iostream>
#include <queue>
using namespace std;

int partition(int a[], int n)
{
    int count=0;
    for (int i=1;i<n; i++)
    {       if (a[i]<a[0])
            count++;
    }
    swap(a[0], a[count]);
    return  count;
}

int main()
{
    int a[]={1,2,3,4,5,6};
    
    cout << partition(a,1);
    
}