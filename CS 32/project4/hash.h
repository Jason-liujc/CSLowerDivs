//
//  hash.h
//  project 4
//
//  Created by Jason on 8/9/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#ifndef __project_4__hash__
#define __project_4__hash__

#include <vector>
#include <list>
#include <iostream>
#include <string>

const int HashConstant=5381;
using std::cout;
using std::vector;
using std::string;
using std::list;

class HashTable {

public:
    HashTable ();
    bool exist(string query);
    void insert(string data);
    string find(string data);
private:
    int MAX_BUCKETS;
    vector<list<string>> buckets;
     unsigned long hash(string data);
};



#endif /* defined(__project_4__hash__) */
