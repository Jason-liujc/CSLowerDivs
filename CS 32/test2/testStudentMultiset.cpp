#include "StudentMultiset.h"
#include <cassert>
using namespace std;

int main ()
{
    StudentMultiset sss;
    sss.add(123);
    assert(sss.size()==1);
    sss.print();
    sss.add(90123);
    assert(sss.size()==2);
    
    
    
}