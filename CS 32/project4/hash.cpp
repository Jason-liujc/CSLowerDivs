//
//  hash.cpp
//  project 4
//
//  Created by Jason on 8/9/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include "hash.h"

unsigned long HashTable::hash(string data)
{
    
    unsigned long key=HashConstant;
    int length=(int)data.length();
    for (int i=0; i<length ; i++)
    {
        key=key*10+data[i];
    }
    
    key=key%MAX_BUCKETS;
    
    return key;
}

HashTable::HashTable (): MAX_BUCKETS(10000) { //constructor
    // Start off the buckets with MAX_BUCKETS
    buckets.resize(MAX_BUCKETS);
    
    
    
}

bool HashTable::exist (string target) {  //got some help from the TA's discussion(Andrew)
  
    unsigned long check=hash(target); //get the key
    list<string>* temp=&buckets[check];
    
    list<string>::iterator j=temp->begin();
    
    while (j != temp->end()) {
        string temp=*j;
        if (temp == target) {
            break;
        }
        j++;
    }
    
    
    if(j!=temp->end())
        return true;
    else
        return false;
    
    
    
}

void HashTable::insert (string data) {
    unsigned long key=hash(data);
    if (exist(data))
        return;
    
    // [!] Push toInsert to the back of the list that the
    // hash function gives you from input toInsert
    buckets[key].push_back(data);
}

