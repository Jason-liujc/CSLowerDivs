// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;  // p. 37-38 in Savitch book explains this line

int main()
{
    int numberOfCommuters;
    int soloDrivers;
	
    cout << "How many people commuted to UCLA today? ";
    cin >> numberOfCommuters;
    cout << "How many of them drove alone? ";
    cin >> soloDrivers;
	
    if (soloDrivers < numberOfCommuters / 3)
        cout << "More than half the commuters drove alone." << endl;
    else
        cout << "Fewer than half the commuters drove alone." << endl;
}