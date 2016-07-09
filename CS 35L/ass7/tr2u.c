#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//If orig char exists in string, replace with replacement char.
char *replace(char *string,  int size,char from, char to)
{
 
  for (int i=0; i<size; i++)
    {
      if (string[i]==from)
      
		string[i]=to;
		
    }

  return string;
}

int main(int argc, char *arr[]){
  
  char* arg1= arr[1];
  char* arg2= arr[2];
  
  
  if ( argc != 3 )
    {
    
     fprintf(stderr, "Hey! Wrong number of arguments! \n");
     
      exit(1);
      
    }

  int temp;
  
  
  ////quick way to check if a character is repeated or not
  int same=0;
  
  for (int i=0;i <strlen(arg1)-1 ; i++)
    {
    
      for (temp=i+1; temp< strlen(arg1); temp++)
      
	 	 if (arg1[i]==arg1[temp]) 
	 	 
		  	same=1;
    }

  if ( same ){
  
    fprintf(stderr, "Argument cannot have repeated characters! \n");
    
    exit(1);
    
  }
  
  if ( strlen(arg1) != strlen(arg2) ){
  
    fprintf(stderr, "Arguments are not the same size! \n");
    
 exit(1);
    
  }

  
  int buffer=2048;
  
  int count=0;
  
  char *size= (char*)malloc(buffer*sizeof(char));

  if (size==NULL){
  
    fprintf(stderr,"Can't allocate memory! \n");
    
    exit(1);
    
  }

  
  int bytes;
  
  
  while (1){
    bytes = read(0,size+count, 1);
    if (bytes == 0)
      break;

    count++;

    if (count == buffer){
    
      size = (char*)realloc(size, buffer*2);
      
      if(size == NULL){
      
		fprintf(stderr,"Can't allocate memory! \n");
	
		exit(1);
		
      }
      
      buffer = buffer*2;
      
    }
    
  }

  int length=strlen(arg1);
  
  for (int k=0; k < length; k++)
    {
      char temp1= arg1[k];
       
      char temp2 = arg2[k];
      
      if (temp1 == temp2)
		continue;


      size = replace(size ,count, temp1, temp2);
      
    }

  //write to stdout
  for (int i=0;i< count; i++)
    write(1, size+i, 1);

  free(size);
  
}