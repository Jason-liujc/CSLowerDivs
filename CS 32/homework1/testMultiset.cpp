    #include "Multiset.h"
    #include <iostream>
    #include <cassert>
    using namespace std;

    int main()
    {
    Multiset ms;
    Multiset ms3;
    assert(ms.empty());
    unsigned long x = 999;
    assert(ms.get(0, x) == 0  &&  x == 999);  // x unchanged by get failure
    assert( ! ms.contains(42));
    ms.insert(42);
    ms.insert(42);
    ms3.insert(55);
    ms.swap(ms3);
        
    assert(!ms3.contains(55));
    assert(ms.contains(55));
    
    assert(ms3.contains(42));
        
       
    assert(ms3.size()==2);
    assert(ms3.uniqueSize()==1);
        assert(ms.insert(56));
        assert(ms3.insert(90));
        
        
        assert(ms3.uniqueSize()==2);
        
        
        
        assert(ms3.insert(-10));
        
        
        assert(ms3.size()==4);
        
       assert(ms3.erase(42));
        
        
        
        assert(ms3.erase(42));
          
        
        assert(ms3.uniqueSize()==2);
        
       
        
        assert(ms3.contains(-10));
        
       
 
        
    }
