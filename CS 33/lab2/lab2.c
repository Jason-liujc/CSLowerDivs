#include <stdio.h>



char *min_ptr = NULL , *max_ptr ;
void endian(unsigned char *p);


void spray_paint( char *x, int sz, char tok, char *t )
   {
   printf( "%p %3d %x %s\n", x,sz,(unsigned char) tok,t ) ;

//
// spray paint code
//
       
//       if (min_ptr == NULL)
//       {
//           min_ptr = x;
//       }
//       if (min_ptr != NULL && min_ptr > x)
//       {
//           min_ptr = x;
//       }
       
       min_ptr=x;
       
       
       if(max_ptr<min_ptr+sz-1)  //the spec says max_ptr should be the highest memory that's spray painted.
       {
           max_ptr=min_ptr+sz-1;
           
       }
    
       
       for(int i=0; i<sz;i++)
       {
           
           *x=tok;

           
           x++;
           
         
       }
           
    
       
       
   }

void dumper( char *x, int n )
   {
//
//   dumper code
//
       
       unsigned long p = *(unsigned long*)&x;
       unsigned char *result;
       p &= ~((unsigned long)0xf); // round down to a multiple of 16
       result = (unsigned char*)p;
       
       //PRINT IN REVERSE!
       //n will always be <= 16
       int g;
       
       for (g = 0; g < n; g++)
       {
           printf("%p  ", (void *)result); // prints the address
           printf("%08x ", *(unsigned int*)result); // prints value
           printf("%08x ", *(unsigned int*)(result +4));
           printf("%08x ", *(unsigned int*)(result +8));
           printf("%08x ", *(unsigned int*)(result +12));
           printf("\n");
           result = result + 16;
           
       }

      
       
       
   }





void sub2()
{
int i ;
char* a ;
char x[20] ;

spray_paint( (char *) &i, sizeof(i), 0xf1, "sub2.i" ) ;
spray_paint( (char *) &a, sizeof(a), 0xf2, "sub2.a" ) ;
spray_paint( (char *) &x, sizeof(x), 0xf3, "sub2.x" ) ;
printf ( "Min= %p Max= %p\n", min_ptr, max_ptr ) ;
dumper( min_ptr,(int) (max_ptr-min_ptr)/16+1 ) ;
//
//   save/destroy the stack here (don't forget to use an external save area)
//
    char *temp2=min_ptr;
    char * temp=min_ptr;
    
    ////////save
    
    int space=(int)(max_ptr-min_ptr);
    
    
    char j[space];
    int count=0;
    
    
    
    
    
    do
    {
        
        j[count]=*temp2;
        
        temp2++;
        
        count++;
        
        
        
    }while(temp2<=max_ptr);
    
    
    
    
    
    
    ///overwrites
    do
    {
        *temp=1;
        
        
        
        temp++;
        
    }while(temp<=max_ptr);
    
    
    
    
    
    
    
    
    
    
    
printf( " destroyed stack\n" ) ;
dumper( min_ptr,(int) (max_ptr-min_ptr)/16+1 ) ;
//
//    restore the stack here
//
    
    char *temp_min=min_ptr;
    char *temp_max=max_ptr;
    
    count=0;
    
    do
    {
        
        *temp_min=j[count];
        
        temp_min++;
        
        count++;
        
    }while(temp_min<=temp_max);
    
   
    
    
    
    
    
    
    
    
    
    
printf( " restored stack\n" ) ;
dumper( min_ptr,(int) (max_ptr-min_ptr)/16+1 ) ;
    
    
    
}






void sub1()
{
float i ;
short a ;
int x[20] ;

spray_paint( (char *) &i, sizeof(i), 0xe1, "sub1.i" ) ;
spray_paint( (char *) &a, sizeof(a), 0xe2, "sub1.a" ) ;
spray_paint( (char *) &x, sizeof(x), 0xe3, "sub1.x" ) ;
sub2() ;
}






int main()
{
    
    
struct mine {
char* a ;
char x[20] ;
float z ;
} i;

union crazy {
float a ;
char b ;
int s ;
} a ;

char x[50] ;

spray_paint( (char *) &i, sizeof(i), 0xd1, "main.i" ) ;
spray_paint( (char *) &a, sizeof(a), 0xd2, "main.a" ) ;
spray_paint( (char *) &x, sizeof(x), 0xd3, "main.x" ) ;

sub1() ;

return 0 ;
    
    
}


void endian(unsigned char *p)
{
//    for(int i=0;i<4;i++)
//        
//    {
//        
//        printf("%x",*p);
//        
//        
//        p++;
//        
//        
//        
//        
//    }
//    
    
    
    
}
