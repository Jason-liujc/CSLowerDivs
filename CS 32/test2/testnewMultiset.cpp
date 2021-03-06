//
//  testnewMultiset.cpp
//  test2
//
//  Created by Jason on 7/2/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include "newMultiset.h"
#include <cassert>
using namespace std;
int main()
{
    
    Multiset a(1000);   // a can hold at most 1000 distinct items
    Multiset b(5);      // b can hold at most 5 distinct items
    Multiset c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    //ItemType v[6] = {"asd", "dsf", "afd", "dass", "ad", "asfd" };
    ItemType v[6]= {1,2,3,4,5,6};
    // No failures inserting 5 distinct items twice each into b
    for (int k = 0; k < 5; k++)
    {
        assert(b.insert(v[k]));
        assert(b.insert(v[k]));
    }
    assert(b.size() == 10  &&  b.uniqueSize() == 5  &&  b.count(v[0]) == 2);
    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    
    // When two Multisets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5])  &&  b.insert(v[5]));
    assert(a.uniqueSize()==5);
//    ItemType teppp;
//    a.get(1,teppp);
//    assert(teppp=="dsf");
//    assert(b.get(2, teppp)==0);
//    
////    a.insert("kkk");
////    assert(a.uniqueSize()==1);
////    a.insert("bbb");
////    a.insert("kkk");
//    assert(a.size()==3);
//    assert(a.uniqueSize()==2);
    
    
}