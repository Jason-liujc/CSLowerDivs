//
//  Multiset.h
//  test2
//
//  Created by Jason on 6/29/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#ifndef __test2__newMultiset__
#define __test2__newMultiset__
#include <iostream>

typedef unsigned long ItemType;
//typedef unsigned long cType;
const int DEFAULT_MAX_ITEMS=200;

class Multiset
{
public:
    Multiset();
     Multiset(int n);    // Create an empty multiset.
    ~Multiset();
    bool empty() const;  // Return true if the multiset is empty, otherwise false.
    
    int size() const;
    // Return the number of items in the multiset.  For example, the size
    // of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.
    
    int uniqueSize() const;
    // Return the number of distinct items in the multiset.  For example,
    // the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
    // "turmeric" is 2.
    
    bool insert(const ItemType& value);
    // Insert value into the multiset.  Return true if the value was
    // actually inserted.  Return false if the value was not inserted
    // (perhaps because the multiset has a fixed capacity and is full).
    
    int erase(const ItemType& value);
    // Remove one instance of value from the multiset if present.
    // Return the number of instances removed, which will be 1 or 0.
    
    int eraseAll(const ItemType& value);
    // Remove all instances of value from the multiset if present.
    // Return the number of instances removed.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the multiset, otherwise false.
    
    int count(const ItemType& value) const;
    // Return the number of instances of value in the multiset.
    
    int get(int i, ItemType& value) const;
    // If 0 <= i < uniqueSize(), copy into value an item in the
    // multiset and return the number of instances of that item in
    // the multiset.  Otherwise, leave value unchanged and return 0.
    // (See below for details about this function.)
    
    void swap(Multiset& other);
    // Exchange the contents of this multiset with the other one.
    
private:
    int m_size;
    ItemType *set=new ItemType[assignedSize];
    int m_unique;
    void changeSize(int size, int unique);
    int assignedSize;
    void changeAss(int assigned);
    void calculateUnique();
    bool isParameter=true;
    
};


#endif /* defined(__test2__Multiset__) */
