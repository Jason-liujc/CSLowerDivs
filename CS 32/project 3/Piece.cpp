//
//  Piece.cpp
//  imitris
//
//  Created by Jason on 7/29/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#include "Piece.h"

Piece::Piece()
{
    
}


//here, each shape if consist of a 3D array of boolean values, by processing it, we can turn this into a 4X4 char array.
// one dimention is for orientation. 


//////////////////////////
//the shape part!!!
//////////////////////////
//////////////////////////
bool *Tpiece::shape()
{
     static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
        { false, true, false, false  },
        { true , true, true , false  },
        { false, false, false, false },
        {false, false, false, false  },
 
        
    },
    
    {
        { false, true, false, false  },
        { false , true, true , false  },
        { false, true, false, false   },
        {false, false, false, false  },
        
 
    },
    
    {
        { false, false, false, false  },
        { true , true, true , false  },
        { false, true, false, false   },
        {false, false, false, false  },
        
        
    },
    
    {
        { false, true, false, false  },
        { true , true, false , false  },
        { false, true, false, false   },
        {false, false, false, false  },
        
        
    }
    };
    
    return **shapie;
    
    
}



bool *Lpiece::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { false, false, false, false  },
            { true , true, true , false  },
            { true, false, false, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, true , true, false  },
            { false , false, true , false  },
            { false, false, true, false   },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, false, false, false  },
            { false ,false, true , false  },
            { true, true,  true, false   },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, false, false, false  },
            { false , true, false , false  },
            { false, true, false, false   },
            {false, true, true, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}


bool *Jpiece::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { false, false, false, false  },
            { false , true, true , true  },
            { false, false, false, true },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, false , false, false  },
            { false , false, true , false  },
            { false, false,  true, false   },
            {false,  true,   true,  false  },
            
            
        },
        
        {
            { false, false, false, false  },
            { false, true, false , false   },
            { false,  true,  true, true   },
            { false, false, false, false  },
            
            
        },
        
        {
            { false, true, true, false    },
            { false, true, false , false  },
            { false, true, false,  false  },
            {false,  false, false,  false  },
            
            
        }
    };
    
    return **shapie;
    
    
}

bool *Opiece::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { true, true, false, false  },
            { true , true, false , false  },
            { false, false, false, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { true, true, false, false  },
            { true , true, false , false  },
            { false, false, false, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { true, true, false, false  },
            { true , true, false , false  },
            { false, false, false, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { true, true, false, false  },
            { true , true, false , false  },
            { false, false, false, false },
            {false, false, false, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}



bool *Spiece::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { false, false, false, false  },
            { false , true, true , false  },
            { true, true , false, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, true, false, false  },
            { false , true, true , false  },
            { false, false, true, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, false, false, false  },
            { false , true, true , false  },
            { true,  true,  false, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, true, false, false  },
            { false , true, true , false  },
            { false, false, true, false },
            {false, false, false, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}



bool *Zpiece::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { false, false, false, false  },
            { true , true, false , false  },
            { false, true , true, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, false, true, false  },
            { false , true, true , false  },
            { false, true, false, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, false, false, false  },
            { true , true, false , false  },
            { false,  true,  true, false },
            {false, false, false, false  },
            
            
        },
        
        {
            { false, false, true, false  },
            { false , true, true , false  },
            { false, true,  false, false },
            {false, false, false, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}


bool *Ipiece::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { false, false, false, false  },
            { true , true,  true , true  },
            { false, false, false, false },
            {false , false, false, false  },
            
            
        },
        
        {
            { false, true, false, false  },
            { false , true, false, false  },
            { false, true, false, false },
            {false, true, false, false  },
            
            
        },
        
        {
            { false, false, false, false  },
            { true , true,  true , true  },
            { false, false, false, false },
            {false , false, false, false  },
            
            
        },
        
        {
            { false, true, false, false  },
            { false , true, false, false  },
            { false, true, false, false },
            {false, true, false, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}


bool *vapor::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { false, true, true, false   },
            { false,false, false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        },
        
        {
            { false, true, true, false   },
            { false,false, false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        },
        
        {
            { false, true, true, false   },
            { false,false, false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        },
        
        {
            { false, true, true, false   },
            { false,false, false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}
bool *foam::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { false, false, false, false   },
            { false, true,  false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        },
        
        {
            { false, false, false, false   },
            { false, true,  false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        },
        
        
        {
            { false, false, false, false   },
            { false, true,  false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        },
        
        
        {
            { false, false, false, false   },
            { false, true,  false, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}


bool *crazy::shape()
{
    static bool shapie[MAXORIENTATION][MAXrow][MAXcol]=
    {
        {
            { true, false, false, true   },
            { false, true,  true, false  },
            { false, false, false, false  },
            {false , false, false, false  },
            
            
        },
        
        {
            { false, false, false, true   },
            { false, false,  true, false  },
            { false, false,  true, false  },
            {false , false, false, true  },
            
            
        },
        
        
        {
            { false, false, false, false   },
            { false, false,  false, false  },
            { false, true, true, false  },
            {true , false, false, true  },
            
            
        },
        
        
        {
            { true, false, false, false   },
            { false, true,  false, false  },
            { false, true, false, false  },
            { true , false, false, false  },
            
            
        }
    };
    
    return **shapie;
    
    
}


/////////////////////////////////////
// The type part!!!!////////////////
////////////////////////////////////

/////
/////  Vapor type=1; foam type=2; crazy type=3; others =0;
/////
int Tpiece::getType()
{
    type=0;
    return type;
}

int Jpiece::getType()
{
    type=0;
    return type;
    
}

int Lpiece::getType()
{
    type=0;
    return type;
}

int Opiece::getType()
{
    
    type=0;
    return type;
}

int Spiece::getType()
{
    type=0;
    return type;
}

int Zpiece::getType()
{
    type=0;
    return type;
    
}

int Ipiece::getType()
{
    type=0;
    return type;
    
}

int vapor::getType()
{
    type=1;
    return type;
}

int foam::getType()
{
    type=2;
    return type;
    
    
}

int crazy::getType()
{
    type=3;
    return type;
    
}




