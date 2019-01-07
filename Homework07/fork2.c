#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
#include <sys/wait.h> /* Needed for avoiding errors. */
int sum;
int main (int argc, char** argv ) {
  int i;
  char input[26]; 
  sum = 0;
  
  int character, n = 0;
// Put it to sleep for 5 seconds 
  printf("Sleeping\n");
  sleep(5);

 while((character = getchar()) != EOF && n<26)
  {
  input[n] = character;
  ++n;
  }

   int is_Child = fork();
 

 // Creating forks and checking if process is child or parent 
  for (i=0; i<=10 ; i++) {
    sum += i;
	 // Checking if the process is the child and sleep for 2 seconds 
	 if(is_Child == 0){
		printf("sum is C%d ", sum);
 		printf("%c\n", input[i]);
		sleep(2);
 	}	
	// Else check if the process is the parent and sleep for 1 second 
 	else{
		printf("sum is P%d ", sum);
		printf("%c\n", input[i]);
		sleep(1);
     	}
   fflush(stdout);
}

// If there is an argument (other than the name of the file being excuted) and you are parent, wait for child "

if(argc > 1 && is_Child != 0)// || argv[1] == "fork.c")
{
	int status;
	wait3( &status, 0, NULL);
	return 0 + status;
}

// If there is no argument (or you are the child ) execute return immediately 
if(argc == 0 || is_Child ==0){
  return 0;
}
return 0;
};
