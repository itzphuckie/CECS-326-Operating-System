/*
   The parser piece for the minishell assignment
   Replace the part that prints the parsed command
   with you code that does the fork, exec, wait.
*/
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> //needed for fork
#include <sys/wait.h> //needed to avoid complier errors
#include <stdlib.h> // needed for fork and wait 
int main()
{
  char line[40];// length of commnd
  char *nargs[10]; // 
  char *space = " ";
  char *where; // pointer 
  
  while(1) // always runnning , infinite loop
  {
    int i = 0;
    printf("Your command please: ");
    fgets(line,sizeof(line),stdin); // user input, ls -> line 
    line[strlen(line)-1] = '\0';
    where = strtok(line,space); // strok - split string into token 
    nargs[i++] = where;
    while (where != NULL)
    {
      where = strtok(NULL,space);
      nargs[i++] = where;
    }
    /* Print the results */
   // printf("Your parsed command was:\n");
    for (i = 0 ; nargs[i] != NULL; i++)
    {
      printf(" %s\n", nargs[i]);
    }
    
    if(fork() == 0){
	execvp(*nargs,nargs); //execute on commad lines 
    }
    else{
	wait(NULL);
    }    
  }
};
