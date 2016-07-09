//
//  StudentMultiset.h
//  test2
//
//  Created by Jason on 6/29/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#ifndef __test2__StudentMultiset__
#define __test2__StudentMultiset__

#include <iostream>


#include "Multiset.h"

class StudentMultiset
{
public:
    StudentMultiset();       // Create an empty student multiset.
    
    bool add(unsigned long id);
    // Add a student id to the StudentMultiset.  Return true if and only
    // if the id was actually added.
    
    int size() const;
    // Return the number of items in the StudentMultiset.  If an id was
    // added n times, it contributes n to the size.
    
    void print() const;
    // Print every student id in the StudentMultiset one per line; print
    // as many lines for each id as it occurs in the StudentMultiset.
    
private:
    Multiset m_student;
    
};


#endif /* defined(__test2__StudentMultiset__) */
