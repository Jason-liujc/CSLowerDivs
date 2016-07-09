//
//  Piece.h
//  imitris
//
//  Created by Jason on 7/29/14.
//  Copyright (c) 2014 Jason. All rights reserved.
//

#ifndef __imitris__Piece__
#define __imitris__Piece__

#include <iostream>
const int MAXORIENTATION=4;
const int MAXrow=4;
const int MAXcol=4;

class Piece
{
public:
    Piece();
    ~Piece(){};
    virtual bool *shape()=0;
    virtual int getType()=0;
    
    
private:
    
    int m_orientaion;
    
    
};


class Tpiece: public Piece
{
public:
    ~Tpiece(){};
    virtual bool *shape();
    virtual int getType();
    
private:
    int type;
    
    
    
};


class Lpiece: public Piece
{
public:
    ~Lpiece(){};
    virtual bool *shape();
    virtual int getType();
    
private:
    int type;
    
    
    
};



class Jpiece: public Piece
{
public:
    ~Jpiece(){};
    virtual bool *shape();
    virtual int getType();
    
    
private:
    int type;
    
    
    
};
class Opiece: public Piece
{
public:
    ~Opiece(){};
    virtual bool *shape();
    virtual int getType();

    
    
private:
    int type;
    
    
    
};


class Spiece: public Piece
{
public:
    ~Spiece(){};
    virtual bool *shape();
    virtual int getType();

    
    
private:
    int type;
    
    
    
};

class Zpiece: public Piece
{
public:
    ~Zpiece(){};
    virtual bool *shape();
    virtual int getType();

    
    
private:
    int type;
    
    
    
};



class Ipiece: public Piece
{
public:
    ~Ipiece(){};
    virtual bool *shape();
    virtual int getType();

    
    
private:
    int type;
    
    
    
};

class vapor: public Piece
{
public:
    ~vapor(){};
    virtual bool *shape();
    virtual int getType();
    
    
private:
    int type;
    
    
    
};

class foam: public Piece
{
public:
    ~foam(){};
    virtual bool *shape();
    virtual int getType();
    
    
private:
    int type;
    
    
};


class crazy: public Piece
{
public:
    ~crazy(){};
    virtual bool *shape();
    virtual int getType();
    
    
private:
    int type;
    
    
    
};
#endif /* defined(__imitris__Piece__) */


