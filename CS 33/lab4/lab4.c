#include <stdio.h>
#include <stdlib.h>

#define HEAPSIZE 32768
//worked with matthew lin, Kevin Huynh
#define hdr_payload(i)  ((struct HDR *) &heap[i])->payload
#define hdr_freeall(i)  ((struct HDR *) &heap[i])->freeall
#define hdr_succesr(i)  ((struct HDR *) &heap[i])->succesr
#define hdr_previus(i)  ((struct HDR *) &heap[i])->previus

char *heap ;
int  heapsize ;

int iterator;
int sizehdr ;

struct HDR       // free block header/footer/linked list
{
    int  payload ;    // size of block (excluding headers)
    char freeall ;    // is this block allocated? 0=free/1=allocated
    int  succesr ;    // successor free block
    int  previus ;    // previous free block
} anchor ;

void dump_heap( char *t )   // prints all of the headers/footers on the heap
{
    int i ;
    
    int j=0 ;
    printf( "%s anchor= %d\n", t, anchor.succesr ) ;
    for( i=0; i<heapsize; i=i+sizehdr  )
        if ( hdr_payload(i) != 0 )
        {
            printf( "%6d %6d %6d %6d %6d\n", i, hdr_payload(i), hdr_freeall(i), hdr_previus(i), hdr_succesr(i) ) ;
            if ( j++%2==1 ) printf( "\n" ) ;
        }
}

void init_heap()   // initialize the heap
{
    heap = (char *) calloc( HEAPSIZE, 1 ) ;
    sizehdr =  16 ;
    heapsize = HEAPSIZE ;
    
    anchor.payload =  0 ;   // anchor
    anchor.freeall =  1 ;
    anchor.succesr =  0 ;
    anchor.previus = -1 ;
    
    hdr_payload(0) = heapsize-2*sizehdr ;   // header
    hdr_freeall(0) = 0 ;
    hdr_succesr(0) = heapsize ;
    hdr_previus(0) = -1 ;
    hdr_payload(heapsize-sizehdr) = heapsize-2*sizehdr ; // footer
    hdr_freeall(heapsize-sizehdr) = 0 ;
}

void lfree( int *aa )   // frees the block at address aa
{
    int index = *(aa) - 16;
    hdr_freeall(index) = 0;
    hdr_freeall(index + hdr_payload(index) + 16) = 0;
    hdr_previus(index) = -1;
    hdr_succesr(index) = anchor.succesr;
    
    if (anchor.succesr != heapsize)
        hdr_previus(anchor.succesr) = index;
    anchor.succesr = index;
    
    if (hdr_freeall(index - 16) == 0 && index != 0)
    {
        int previousheader = index - hdr_payload(index - 16) - 32;
        
        hdr_payload(previousheader) = hdr_payload(previousheader) + hdr_payload(index) + 32;
        
        hdr_payload(index + hdr_payload(index) + 16) = hdr_payload(previousheader);
        
        memset(&heap[index - 16 - hdr_payload(index - 16)], 0, hdr_payload(previousheader));
        hdr_previus(previousheader) = -1;
        index = previousheader;
        anchor.succesr = index;
        if (index + hdr_payload(index) + 32 == heapsize)
        {
            iterator = index;
        }
    }
    if (hdr_freeall(index + hdr_payload(index) + 32) == 0 && (index + hdr_payload(index) + 32) != heapsize)
    {
        int sHeader = index + hdr_payload(index) + 32;
        int ssHeader = hdr_succesr(sHeader);
        int sFooter = sHeader + hdr_payload(sHeader) + 16;
       
        int prevheader = hdr_previus(sHeader);
        
        //marking the header and footer
        hdr_payload(index) = hdr_payload(index) + hdr_payload(sHeader) + 32;
        hdr_payload(sFooter) = hdr_payload(index) + hdr_payload(sHeader) + 32;
        
        
        hdr_succesr(prevheader) = ssHeader;
        
        if (ssHeader != heapsize)
        {
            hdr_previus(ssHeader) = prevheader;
        }
        hdr_previus(index) = -1;
        memset(&heap[index + 16], 0, hdr_payload(index));
    }
    // lfree code here
}

int lalloc( int amt )   // allocates a block of size int
{
    // lalloc code here
	   int blockSize;	//Represents the total size of a block
	   int payloadAddress;	//Default value of testing
	   
	   int freeBlockPayload;
    
       int perfectFitFooter;
	   int splitFitFooter;
    
	   int newFreeBlock;
	   //Use first fit to find a block, round up to multiple of 16
	   int remainder = amt % sizehdr;
	   if (remainder != 0)			//If amount does NOT divide evenly
           amt += sizehdr - remainder;	//new payload size will be a multiple of 16
    
    iterator = anchor.succesr;
    
	   
	   blockSize = amt + 2*sizehdr;
	   payloadAddress = -69;
    
	   while (iterator <= heapsize)
       {
           
           perfectFitFooter = iterator + blockSize + sizehdr;
           splitFitFooter = iterator + amt + sizehdr;
           
           int tempIndex = 0;
           if (hdr_succesr(iterator) == heapsize)
           {
               tempIndex = iterator;
           }
           if (iterator == heapsize) //find payload of one before the end, if it is free. add that to the number. do division, if modulo is not one, add one. to the number. do a for loop and realloc that many times.
           {
              
               while(heapsize<=blockSize) // increase the heapsize
                   
               {
               heapsize = heapsize + HEAPSIZE;
               
               heap = (char *) realloc (heap, heapsize);
                   
               }
               
               
               
               hdr_payload(iterator) = HEAPSIZE - 32;
               
               hdr_succesr(tempIndex) = heapsize;
               
               hdr_payload(heapsize - 16) = HEAPSIZE - 32;
               
               int* j = (int *) &heap[iterator + 16];
               
               lfree(j);
               
               dump_heap( "blew the top off" ) ;
               
               break;
               
            }
           
           if (blockSize <= hdr_payload(iterator))
           {
               if(hdr_payload(iterator) == blockSize)		//perfect fit
               {
                   
                   //header
                   hdr_payload(iterator) = blockSize;
                   hdr_freeall(iterator) = 1;
                   
                   //footer
                   hdr_payload(perfectFitFooter) = blockSize;
                   hdr_freeall(perfectFitFooter) = 1;
                   
                   if (hdr_succesr(iterator) == heapsize)					//last block
                       hdr_succesr(hdr_previus(iterator)) = heapsize;
                   
                   
                   if (hdr_previus(iterator) == -1)		//first block
                   {
                       anchor.succesr = hdr_succesr(iterator);
                       hdr_previus(anchor.succesr) = -1;
                   }
                   
                   
                   
                  
                   
                   
                   
                   if (hdr_previus(iterator) != -1 && hdr_succesr(iterator) != heapsize)		//Middle block
                   {
                       hdr_succesr(hdr_previus(iterator)) = hdr_succesr(iterator);
                       hdr_previus(hdr_succesr(iterator)) = hdr_previus(iterator);
                       
                    
                   }
                   
                   hdr_previus(iterator) = 0;
                   
                   hdr_succesr(iterator) = 0;
                  
                   payloadAddress = iterator + sizehdr;
                   return payloadAddress;
               }
               
               else if (blockSize < hdr_payload(iterator))		//dividing
               {
                   freeBlockPayload = hdr_payload(iterator) - blockSize;
                   
                   //header
                   hdr_freeall(iterator) = 1;
                   
                   hdr_payload(iterator) = amt;

                   //footer
                   hdr_freeall(splitFitFooter) = 1;
                   
                   hdr_payload(splitFitFooter) = amt;
                  
                   
                   //Set the return address
                   payloadAddress = iterator + sizehdr;
                   newFreeBlock = iterator + blockSize;
                   
                   //Split the block and create a new free block
                   //header
                   hdr_payload(newFreeBlock) = freeBlockPayload;
                   hdr_freeall(newFreeBlock) = 0;
                   
                   //footer
                  
                   hdr_freeall(newFreeBlock + freeBlockPayload + sizehdr) = 0;
                   
                    hdr_payload(newFreeBlock + freeBlockPayload + sizehdr) = freeBlockPayload;
                   //Adjust the pointers
                   
                   if (hdr_previus(iterator) == -1)
                       anchor.succesr = newFreeBlock;
                   
                   else
                       hdr_succesr(hdr_previus(iterator)) = newFreeBlock;
                   
                    hdr_succesr(newFreeBlock) = hdr_succesr(iterator);
                   
                   hdr_previus(newFreeBlock) = hdr_previus(iterator);
                   
                   hdr_payload(newFreeBlock) = freeBlockPayload;
                   
                   if (hdr_succesr(iterator) == heapsize && hdr_previus(newFreeBlock) != -1)
                       hdr_previus(hdr_succesr(iterator)) = newFreeBlock;
                   
                   
                   hdr_succesr(iterator) = 0;
                   
                   hdr_previus(iterator) = 0;
                 
                   
                   payloadAddress = iterator + sizehdr;
                   return payloadAddress;
               }
           }
           
           
           if (iterator != heapsize)
               iterator = hdr_succesr(iterator);
       }
    
    
    
	   return payloadAddress;
}



int main()
{
    int i ;
    int j = 0  ;
    int blks[100] ;
    
    init_heap() ;
    dump_heap( "init heap" ) ;
    
    for( i=0; i<20; i++ )
        blks[j++] = lalloc( rand()%500 ) ;
    dump_heap( "first allocs" ) ;
    
    lfree( &blks[10] ) ;
    lfree( &blks[11] ) ;
    dump_heap( "coalesce with upper" ) ;
    
    lfree( &blks[14] ) ;
    lfree( &blks[13] ) ;
    dump_heap( "coalesce with lower" ) ;
    
    lfree( &blks[5] ) ;
    lfree( &blks[7] ) ;
    lfree( &blks[6] ) ;
    dump_heap( "coalesce with both" ) ;
    blks[5] = lalloc( 80000 ) ;
    dump_heap( "blew the top off" ) ;
    
    for( i=0; i<20; i++ )
        if (blks[i] != 0 )
        {
            lfree( &blks[i] ) ;
        }
    dump_heap( "free everything " ) ;
    
    return 0 ;
}

