#include <stdio.h>
#include <stdlib.h>

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

int frobcmp( const char *a,  const char *b)
{
 
 	
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
 
 char *buffer = (char *) malloc(sizeof(char) * 512);
 
 if (buffer == NULL) {
 
  fprintf(stderr, "Something wrong during the memory allocation!"); 
  exit(1); 
  
 }
 int size = 512; 
 
 int k = 0;   // k is a counter here

 int isEmpty = 1; // check for empty file
 

// make sure it reaches the end of the file
 while (1) { 
  char c =  getchar();
  
  if (c == EOF)
  	break;
  	
  isEmpty = 0; 
  
  buffer[k++] = (char) c;
  
  if (k == size) {
  
  
   size*=2;
   buffer = (char*) realloc(buffer, size);
   
   if (buffer == NULL) { 
    fprintf(stderr, "Something wrong during the memory allocation!"); 
    
    
    exit(1);
   } 
   
  } 
 }

// is it empty?
 if (isEmpty == 1) 
 	return 0;
 
// add spaces 
 if (buffer[k-1] != ' ') {
 
  buffer[k++] = ' '; 
  if (k == size) { 
  	size+=32;
  	
   	buffer = (char*) realloc(buffer, size);
   
   	if (buffer == NULL) {   
   
  	  fprintf(stderr, "Something wrong during the memory allocation!"); 
    
  	  exit(1);
    
    
   }
     
  }
 }
 
 char **words = NULL; 
 int word_count = 0; 
 
 
 //qsort(words, word_count, sizeof(char*), cmp); 
 
 
 for (int i = 0; i < k; i++) {
 
  if (i == 0 || buffer[i-1] == ' ') {
  
  	 words = realloc(words, sizeof(char *) * (word_count + 1));
  	 
  	 
   	if (words == NULL) {
   	 /* return error */
   		 fprintf(stderr, "Something wrong during the memory allocation!");
   		  
   		 exit(1);
   		 
  		 }
  		 
  		 
 	  words[word_count++] = &buffer[i];}
 	 
 }
 
 qsort(words, word_count, sizeof(char*), cmp); 
 
 
 
 
 for (int i = 0; i < word_count; i++) {
 
  char *ptr = words[i];
  
  	while (*ptr != ' ') {
  	
   	fprintf(stdout, "%c", *ptr);
   	
  	 ptr++;
  	 
  	 
 	 }
  	fprintf(stdout, "%c", *ptr);
 }
  
//free up stuff
 free(words);
 free(buffer);
 return 0; 
}