#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#define S       16     //  (16 cache sets)
#define E       4      //  (4-way associative cache)
#define B       32     //  (32 elements in each block)
#define T       7      //  (7 tag bits)
#define M       65536  //  (65536 location memory)
#define READ    1
#define WRITE   0

int s ;
int b ;
int m ;

int rhits = 0 ; int rmiss = 0 ; int whits = 0 ; int wmiss = 0 ; int dwrit = 0 ;

struct cache_t
{
    char dirty ;
    char valid ;
    int  tag   ;
    int 	last  ;
    int  *block ;
} cache[S][E] ;

int *memory ;

int callno = 0 ;

int x  =     0 ;
int y  = 16384 ;
int z  = 32768 ;
int ni =    20 ;
int nj =    20 ;

void stats( char *t )
{
    int i,j,k,A ;
    
    for( i=0; i<S; i++ )
        for( j=0; j<E; j++ )
        {
            if( cache[i][j].valid & cache[i][j].dirty )
            {
                A = cache[i][j].tag*exp2(m-T)+i*B ;
                for( k=0; k<B; k++ )
                    memory[A+k] = cache[i][j].block[k] ;
                dwrit = dwrit+1 ;
            }
            cache[i][j].valid = 0 ;
            cache[i][j].dirty = 0 ;
        }
    
    printf( "%8s y=%5d ni=%5d nj=%5d rh=%5d rm=%5d wh=%5d wm= %5d dw=%5d\n", t, y,ni,nj,
           rhits, rmiss, whits, wmiss, dwrit ) ;
    rhits = 0 ; rmiss = 0 ;
    whits = 0 ; wmiss = 0 ;
    dwrit = 0 ;
    
}

void initcache()
{
     //
    // put code to calculate s, b, m here
    //
    s=log2(S);
    b=log2(B);
    m=log2(M);
    
    
   
    printf( "S= %d E= %d B= %d T= %d M= %d s= %d b= %d m= %d\n", S,E,B,T,M,s,b,m ) ;
    
    //
    // put code to initialize cache and memory here
    //
    
    //doubtful
    
    for(int i=0;i<S;i++)
    {
        for(int j=0; j<E;j++)
        {
            
            cache[i][j].block=(int*)malloc(B* sizeof(int));
            
            cache[i][j].valid=0;
            
            cache[i][j].dirty=0;
            
            cache[i][j].tag=0;
            
            cache[i][j].last=0;
        }
    
        
    }
    
    memory=(int*)malloc(M*sizeof(int));
    
    for (int k = 0; k < M; k++)
        memory[k] = k;
}

void readwritecache( int readwrite, int a, int *value, int *hitmiss, int voice )
{
    
    //
    // readwrite = READ (1) for read, WRITE (0) for write
    // a = binary memory address ( 0 <= a < 65535 ) to read or write
    // *value is memory value returned when readwrite = READ
    //           memory value to store when readwrite = WRITE
    // hitmiss is set to 0 for a miss, 1 for a hit, in either read or write case
    // voice is a debugging switch
    //
    //
    //   compute si, ta, and bo from the address a
   
    
    int i,j;    //iterator
    
    
    
    int si, ta, bo, li ;
    //	si = stack, index
    //	ta = tag
    //	bo = block offset
    //      increment callno
    //
    
//    si = (a >> b) & ((1 << s) - 1);
//    ta = (a >> (b + s)) & ((1 << T) - 1);
//    bo = a & ((1 << b) - 1);
   
    si=(a>>(m-T-s))%S;
    
    ta=a>>(m-T);
    
    bo=a%B;
    
    
    int siz=sizeof(int)*B;
    
    int ba=0;
    
    
    callno++;
    
    
    
    
    if( voice )
        printf( "%5d rw= %d a= %5d bo= %3d si= %3d ta= %3d", callno,readwrite,a,bo,si,ta ) ;
    
    //
    //   check each line of the set:
    //	if( cache[si][line#].valid && cache[si][line#].tag = ta )
    //	to find a hit
    //
    //   if no hit, choose a line (not valid or LRU )
    //
    //   if chosen line dirty, copy to memory
    //
    int temp;
    *hitmiss=0;

    
    
    for(temp=0;temp<E;temp++)
    {
        
        
        
        if(cache[si][temp].valid && cache[si][temp].tag==ta)
            
        {
            
                *hitmiss=1;
            
                if (readwrite==READ)		//instruction is read
                {
                    *value = cache[si][temp].block[bo];
                    
                    rhits++;
                    
                    cache[si][temp].last=callno;

                    break;
                }
                
                else		//instruction is write
                {
                    cache[si][temp].block[bo] = *value;
                    
                    cache[si][temp].dirty = 1;
                    
                    whits++;
                    
                    cache[si][temp].last=callno;

                    break;
                }
            
        }
        

        
    }
    
    li=temp;
    
    
    
    
    
    if(*hitmiss == 0) //if miss
    {
        
        
        if (readwrite==READ)   //decide what kind of miss it is, update counter.
        {
            rmiss++;
        }
        else
        {
            wmiss++;
        }
        
        
        
        int index = 0;					//The Index of the minimum

        int Last = cache[si][index].last;		//The value of the minimum
        
      
        
        for (li = 0; li < E; li++) // find the minium index
        {
            
            if(cache[si][li].valid && cache[si][li].last < Last)		//Update minimum value and index if the current element is less than LRU and valid
            {
                Last = cache[si][li].last;
                index = li;
            }
            
            if(readwrite==READ)
            {
                if (!cache[si][li].valid)
                {
                    cache[si][li].valid = 1;
                    
                    memcpy(cache[si][li].block,(memory + (a - bo)), siz);
                    
                    *value = cache[si][li].block[bo];
                    
                    cache[si][li].last =callno;
                    
                    break;
                }
                
                if (li == E-1 ) //if all lines are valid.
                {
                    if (cache[si][index].dirty)
                    {
                        dwrit++;
                        
                         cache[si][index].dirty = 0;
                        
                        ba = (cache[si][index].tag << (s + b)) + (si << b);
                        
                        memcpy(memory + ba, cache[si][index].block, siz);
                        
                       
                        
                        
                    }
                    
                    cache[si][index].tag = ta;
                    
                    memcpy(cache[si][index].block, memory + (a - bo),siz);
                    
                    *value = cache[si][index].block[bo];
                    
                    cache[si][index].valid = 1;
                    
                    cache[si][index].last = callno;  //update it
                }
            }
            
            if(readwrite==WRITE)	//write miss
            {
                if(!cache[si][li].valid)
                {
                    cache[si][li].valid = 1;
                    
                    
                    cache[si][li].block[bo] = *value;
                    
                    cache[si][li].last =callno;
                   
                    cache[si][li].dirty = 1;
                    break;
                }
                
                if(li == E - 1)		//if all lines are valid
                {
                    if(cache[si][index].dirty)
                    {
                        
                         dwrit++;
                        
                        ba = (cache[si][index].tag << (s + b)) + (si << b);
                        
                        
                        memcpy(memory + ba, cache[si][index].block, siz);
                        
                        
                    }
                    
                        memcpy(cache[si][index].block, memory + (a - bo), siz);
                    
                        cache[si][index].block[bo] = *value;
                    
                        cache[si][index].last = callno;  //update it
                    
                        cache[si][index].dirty = 1;
                    
                        cache[si][index].tag = ta;
                    
                        
                }
            }
        }
    }
    
    
    
    
   
    
    
    
    if( voice )
        printf( "li= %d", li ) ;
   
    
    
    
    
    
    if( voice )
        printf( " %d %d %d\n", *value, cache[si][li].valid, cache[si][li].dirty ) ;
}





void locationexample()
{
    int i,j,k,hm, r;

   
    
    for( y=16374; y< 16395; y=y+1 )
    {
        for( i=0; i<nj;i++ )
        {
            readwritecache( READ,   x+i, &r, &hm, 0 ) ;
            readwritecache( WRITE,  y+i, &r, &hm, 0 ) ;
        }
        stats( "loc copy" ) ;
    }
    
    
    //
    // code for row wise transponse
    //
    
    for(i=0;i<ni;i++)
    {
        for(j=0;j<nj;j++)
        {
            readwritecache(READ, y + nj*i + j, &r, &hm, 0);
            readwritecache(WRITE, x + nj*j + i, &r, &hm, 0);
            
        }
         stats( "loc rows" ) ;
    } ///!!!!!!!!!!!!!!!!!!!!
    
    
    
    
    
    
    //
    // code for col wise transponse
    //
    
    for(j=0;j<nj;j++)
    {
        for (i=0;i<ni;i++)
        {
            readwritecache(READ, y + nj*i + j, &r, &hm, 0);
            
            readwritecache(WRITE, x + nj*j + i, &r, &hm, 0);
            
            
        }
    
    
    
    
    stats( "loc cols" ) ;
    }
}

void wsexample()
{
    int i,j,ii,jj,hm,r ;
   
    
    y = 20000 ;
    for( ni=88; ni<128; ni=ni+8 )
    {
        nj = ni ;
        //
        // code for row wise transpose
        //
        
        
        for(i=0;i<ni;i++)
        {
            for(j=0;j<nj;j++)
            {
                readwritecache(READ, y + nj*i + j, &r, &hm, 0);
                readwritecache(WRITE, x + nj*j + i, &r, &hm, 0);
                
            }
            
        }
        
        
        
        
        
        stats( "ws rows" ) ;
    }
    
    for( ni=88; ni<128; ni=ni+8 )
    {
        nj = ni ;
        //
        // code for row wise transpose with 8x blocking
        //
        
        for(ii=0;ii<ni;ii=ii+8)
            for(jj=0;jj<nj;jj=jj+8)
                for (i=ii; i<ii+8; i++)
                    for(j=jj;j<jj+8;j++)
                    {
                        
                        readwritecache(READ, y + nj*i + j, &r, &hm, 0);
                        readwritecache(WRITE, x + nj*j + i, &r, &hm, 0);
                    }
        
        
        
        
        stats( "wsbrows" ) ;
    }
    
    for( ni=88; ni<128; ni=ni+8 )
    {
        nj = ni ;
     
        for(j=0;j<nj;j++)
        {
            for(i=0;i<ni;i++)
            {
                readwritecache(READ, y + nj*i + j, &r, &hm, 0);
                readwritecache(WRITE, x + nj*j + i, &r, &hm, 0);
                
            }
            
        }
        
        
        
        stats( "ws cols" ) ;
    }
    
    for( ni=88; ni<128; ni=ni+8 )
    {
        nj = ni ;
        //
        // code for col wise transpose with 8x blocking
        //
        
        for(jj=0;jj<nj;jj=jj+8)
            for(ii=0;ii<ni;ii=ii+8)
                for(j=jj;j<jj+8;j++)
                    for(i=ii;i<ii+8;i++)
                    {
                        
                        readwritecache(READ, y + nj*i + j, &r, &hm, 0);
                        readwritecache(WRITE, x + nj*j + i, &r, &hm, 0);
                    }
        
        
        stats( "wsbcols" ) ;
    }
    
}

int main()
{
    
    initcache() ;
    locationexample() ;
    wsexample() ;
    
    return 0 ;
}