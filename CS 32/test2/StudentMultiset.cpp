//
//  StudentMultiset.cpp
//  test2
//
//  Created by Jason on 6/29/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include "StudentMultiset.h"


int StudentMultiset::size()const
{
    return  m_student.size();
    
    
}

bool StudentMultiset::add(unsigned long id)
{
    
    if (!m_student.insert(id))
        return  false;
    else
        return true;
    
    
    
}

void StudentMultiset::print() const
{
    ItemType id;
    for (int i=0; i<m_student.size();i++)
    {
        m_student.get(i,id);
        
        
        std::cout <<id << "\n";
    }
    
    
    
    
}


StudentMultiset::StudentMultiset()
{
    
}


