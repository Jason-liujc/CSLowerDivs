
//  Homework
//
//  Created by Jason on 10/11/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include <stdio.h>

// The idea was taken from the textbook.

int main()
{
    int y=0x01234567;
    char * x=(char *)&y;
    
    
    char *p=x;
   
    
    if (*p==0x67){
        printf("little");
    }
    else
    {
        printf("big");
    }
    
  
    
    
}