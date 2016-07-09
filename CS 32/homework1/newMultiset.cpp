//
//  Multiset.cpp
//  test2
//
//  Created by Jason on 6/29/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include "newMultiset.h"

Multiset::Multiset()
{
    isParameter=false;
    assignedSize=DEFAULT_MAX_ITEMS;
    
    m_size=0;
    m_unique=0;
    
    
}

Multiset::~Multiset()
{
   delete []set;
    
    
    
}

Multiset::Multiset(int n)
{
    
    
    if (n<0 or n>DEFAULT_MAX_ITEMS)
        exit(1);
    
    m_unique=0;
    m_size=0;
    
    assignedSize=n;
    
}

bool Multiset::empty() const // Return true if the multiset is empty, otherwise false.
{
    if (m_size==0)
    {
        return true;
        
    }
    else
        return false;
    
}
int Multiset::size() const
// Return the number of items in the multiset.  For example, the size
// of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.
{
    
    return m_size;
}

int Multiset::uniqueSize() const
// Return the number of distinct items in the multiset.  For example,
// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
// "turmeric" is 2.
{
    int counter2=0;
    Multiset ms2;  //create a ms2 object to figure out the unique size.
    
    for (int i=0; i<m_size ; i++)
        // copy all the strings from the this set to the new Multiset I created in this function.
    {
        ms2.insert(set[i]);
        
        
    }
    
    for (int i=0; i<ms2.size(); i++)
    {
        if (ms2.count(set[i])!=1)
        {
            ms2.erase(set[i]);
            
                    counter2++;
           
            
        }
        
    }
    return m_size-counter2;
}


bool Multiset::insert(const ItemType& value)
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full).

{
    
    if (m_unique<assignedSize or contains(value))
    {
       
        set[m_size]=value;
        
        m_size++;
        return true;
        
    }
    else
        return false;
    
    
    calculateUnique();
    
}


int Multiset::erase(const ItemType& value)
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.

{
    int counter=0;
    int counter2=0;
    
    
    while (counter<m_size)
    {
        if (set[counter]==value)
        {
            
            
            counter2=counter;
            while(counter2<m_size)
            {
                set[counter2]=set[counter2+1];
                
                
                counter2++;
            }
            m_size--;
            
            return 1;
        }
        
        counter++;
    }
    
    return 0;
    
    
    calculateUnique();
}

int Multiset::eraseAll(const ItemType& value)
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.
{
    int stored;
    stored=m_size;
    
    m_size=0;
    
    return stored;
}


bool Multiset::contains(const ItemType& value) const
// Return true if the value is in the multiset, otherwise false.
{
    for (int i=0; i< m_size; i++)
    {
        
        if (value==set[i])
            return true;
        
        
        
    }
    
    
    return false;
    
}

int Multiset::count(const ItemType& value) const
// Return the number of instances of value in the multiset.
{
    int counter3=0;
    for (int i=0; i< m_size; i++)
    {
        if (value==set[i])
            counter3++;
        
        
        
    }
    return counter3;
    
    
}
int Multiset::get(int i, ItemType& value) const


// If 0 <= i < uniqueSize(), copy into value an item in the
// multiset and return the number of instances of that item in
// the multiset.  Otherwise, leave value unchanged and return 0.
// (See below for details about this function.)
{
    if (i<0 or i>=uniqueSize())
    {
        return 0;
        
        
    }
    else{
        value=set[i];
        return count(value);
        
    }
    
    
}

void Multiset::swap(Multiset& other)
// Exchange the contents of this multiset with the other one.
{
  
    
    //first swap the items;
   ItemType *temp=new ItemType[assignedSize];
    
    
    if (m_size>=other.m_size)
    {
    
    
        for (int i=0; i<other.m_size; i++)
        {
            temp[i]=other.set[i];
            

            other.set[i]=set[i];
            
            
            set[i]=temp[i];
            
            
          
            
        }
        
        for(int k=other.m_size; k<m_size; k++)
            {
                
                other.set[k]=set[k];
                
            }
    }
    else{
        
        for (int i=0; i<m_size; i++)
        {
            temp[i]=other.set[i];
            
            
            other.set[i]=set[i];
            
            
            set[i]=temp[i];
        }
        
    
        for(int k=m_size; k<other.m_size; k++)
        {
            
            set[k]=other.set[k];
            
        }
            

        
        
        
        
    }
    
    //then swap the size;
   
    
    int tempSize=0;
    
    tempSize=other.size();
    
    int tempSize2;
    tempSize2=m_size;
    
    int tempU1=other.uniqueSize();
    int tempU2=uniqueSize();
    
    
    changeSize(tempSize, tempU1);
    other.changeSize(tempSize2, tempU2);
    
    
    int tempAssigned1=other.assignedSize;
    int tempAssigned2=assignedSize;
    changeAss(tempAssigned1);
    other.changeAss(tempAssigned2);
     tempAssigned1=other.assignedSize;
     tempAssigned2=assignedSize;
    
    calculateUnique();
    other.calculateUnique();

    
    delete []temp;
}

void Multiset::changeSize(int size, int unique)
{
    
    m_size=size;
    m_unique=unique;
    
    
}

void Multiset::changeAss(int assigned)
{
    assignedSize=assigned;
    
    
}
void Multiset::calculateUnique()
{
    
    m_unique=uniqueSize();
    
    
}

