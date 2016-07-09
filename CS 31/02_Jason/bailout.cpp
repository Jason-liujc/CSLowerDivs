#include <iostream>
#include <iomanip>
using namespace std;


int main ()
{
    string companyName;
    double annualSale;
    string industryName;
    int numberEmployees;
    double moneyBorrow1;
    double moneyBorrow2;
    cout << "Company name: ";
    
    getline(cin, companyName);
    
    if (companyName==" ")
    {
        cout << "---" <<endl;
        cout << "You must enter a company name." << endl;
        return 1;
    }
    
    
    cout << "Annual sales (in trillions): " ;
    
    cin >> annualSale;
    
    if (annualSale<0)
    {
        cout << "---" <<endl;
        cout << "The annual sales must be nonnegative." << endl;
        return 1;
    }
    cout << "Industry: ";
    cin.ignore(10000,'\n');
    
    getline(cin,industryName);
    
    
    if (industryName==" ")
    {
        cout << "---" <<endl;
        cout << "You must enter an industry." <<endl;
        return 1;
    }
    
    cout << "Number of employees: ";
    
    cin >> numberEmployees;
    
    
    if (numberEmployees<0)
    {
        cout << "---" <<endl;
        cout << "The number of employees must be positive." <<endl;
        return 1;
    }
    
    
    cout << "---"<<endl;
    
    if (annualSale<500)
    {
        moneyBorrow1=annualSale*0.20000;
    }
    else
    {
        
        if (annualSale<900)
        {
            
            if (industryName=="mud"||industryName=="phishing")
            {
                moneyBorrow1=(annualSale-500)*0.15+100;
            }
            else{
                moneyBorrow1=(annualSale-500)*0.10+100;
            }
        }
        
        else
        {
            
            if (industryName=="mud"||industryName=="phishing")
            {
                moneyBorrow1=100.000+60.000+(annualSale-900)*0.03;
            }
            else
            {
                moneyBorrow1=100.000+40.000+(annualSale-900)*0.03;
            }
            
            
        }
        
        
        
        
    }
    if (annualSale>=700)
    {
        moneyBorrow2=moneyBorrow1+numberEmployees*0.01;
    }
    
    else
    {
        moneyBorrow2=moneyBorrow1;
    }
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    cout << companyName << " can borrow up to G"  << moneyBorrow2 << " trillion." <<endl;
    
    
}