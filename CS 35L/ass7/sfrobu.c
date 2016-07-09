#include <stdio.h>
#include <stdlib.h>


/// for sys call  ////

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

///////////////////////



// 
// void * memfrob (void *s, size_t n)
// {
//     char *p = (char *) s;
//     
//     while (n-- > 0)
//         *p++ ^= 42;
//         
//     return s;
//     }

int compare=0;


int frobcmp( const char *a,  const char *b)
{
 	compare++;
 	
   while (*a == *b && *a != ' ') {

  a++;
  b++;
 }
  
 if (*a == *b) { return 0; } 
 //prefix situation and null situation
 else if (*a == ' ') 
 	return -1; 
 else if (*b == ' ') 
 	return 1; 
 else if (*a == '\0' )
 	return -1;
 else if (*b == '\0')
 	return 1;
 else {
   char *c=(char *)a;
   
   
   *c ^= 42;
   
   char *d=(char *)b;
   *d ^= 42; 
  
  
  	int diff=*c-*d;
  	
  	*c ^= 42;
  	*d ^= 42; 
  
  
  	return diff;


	}
 
  
}



// for the signiture
int cmp (const void *a, const void *b) {
 
 	return frobcmp( *(const char**)a, *(const char**)b ); 
 	
}

int main() {
 struct stat file;
 int size = 2048; 
 fstat(0,&file);
 
 
 int fileSize=0;
 
 fileSize=file.st_size;
 
 
 char *buffer;
 
 //check the file type
 if (!S_ISREG(file.st_mode))
 	buffer=(char*)malloc(size*sizeof(char));
 else
 	buffer=(char*)malloc(fileSize*sizeof(char));
 
 
 
 
 if (buffer == NULL) {
 
  fprintf(stderr, "Something wrong during the memory allocation!"); 
  exit(1); 
  
 }
 
// int count=0;
 int k = 0;   // k is a counter here
 char c;
 int isEmpty = 1; // check for empty file
 

// make sure it reaches the end of the file
 while (read(0, k+buffer, 1)) { 
 
  if(file.st_size != fileSize &&(S_ISREG(file.st_mode)))
 	buffer= (char*)realloc(buffer,file.st_size);
 
 
  if (k == size && (!S_ISREG(file.st_mode)))
 	{

  
   size*=2;
   buffer = (char*) realloc(buffer, size);
   
   	if (buffer == NULL)
     { 
    	fprintf(stderr, "Something wrong during the memory allocation!"); 
   		exit(1);  
 	 } 
   }
  	k++;
 }



// is it empty?
 if (k < 1) 
 	return 0;
 
// add spaces 
 if (buffer[k-1] != ' ') {
 
 

  
  if (k >= size) { 
  
  	size*=2;
  	
   	buffer = (char*) realloc(buffer, size);
   
   	if (buffer == NULL) {   
   
  	  fprintf(stderr, "Something wrong during the memory allocation!"); 
    
  	  exit(1);
    
    
   }
   size*=2;
     
  }
  k++;
  buffer[k-1]=' ';
  
 }
 
 char **words = NULL; 
 int word_count = 0; 
 
 for (int i=0;i<k;i++)
 {
 	if(buffer[i]==' ')
 		word_count++;
 }
 


	words=(char**)malloc(word_count*sizeof(char*));
	

   	if (words == NULL) {
   	 /* return error */
   		 fprintf(stderr, "Something wrong during the memory allocation!");
   		  
   		 exit(1);
   		 
  		 }
  	
  	
  	words[0]=&buffer[0];
  	
  	int count;
  	count=1;
  	
  for (int i=0; i<k; i++){
  
    if(buffer[i]==' ' && i<k-1)
    {
    
      words[count]= &buffer[i+1];
      
       count++;
       
    }
    
  }
 
 	if(count!=word_count)
 	{
 		fprintf(stderr,"Something is wrong! \n");	
 		exit(1);	
 		
 	}
 
 qsort(words, count, sizeof(char*), cmp); 
 
 
 
 
 for (int i = 0; i < count; i++) {
 
  char *ptr = words[i];
  
  	while (1) {
  	
  		write(1,&*ptr,1);
  		
  		if(*ptr==' ')
  			break;
  		ptr++;
  	 
 	 }
 }
 
 
  
//free up stuff
 free(words);
 free(buffer);
 
 fprintf(stderr,"Comparisons: %d\n",compare);
 
 return 0; 
}