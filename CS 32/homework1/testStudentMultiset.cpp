#include "StudentMultiset.h"
#include <cassert>
using namespace std;

int main ()
{
    StudentMultiset sss;
    sss.add(123);
    sss.add(123123);
    assert(sss.size()==2);
    
    sss.add(90123);
    assert(sss.size()==3);
    sss.add(123);
     sss.print();
    
}