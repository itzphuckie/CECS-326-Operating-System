#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int toParent[2], toChild[2];
 // char obuf[20], ibuf[20], eval;
  // Making Pipes
  pipe(toParent); pipe(toChild);
  

  //strcpy(obuf,"Hello\n");
  if (fork()==0) {
      for(int i =0; i<5; i++){
    	close(toParent[0]); /* child */
    	close(toChild[1]);
    // Creating variables needed for both parent and child process
	int multiplicand;
	int multiplier;
	int result;
	// Reading the multipliAnd from the pipe 
	read(toChild[0], &multiplicand, sizeof(multiplicand));
	// Reading the multiplier from the pipe 
	read(toChild[0], &multiplier, sizeof(multiplier));
	// Method to multiply 
	result = multiplicand * multiplier;
	// Write the result to the "result" pipe
	write(toParent[1],&result,sizeof(result));
    //write(toParent[1],obuf,20);
    //read(toChild[0],ibuf,20);
     }
  } else {
      for(int i =0; i<5; i++){	
    	close(toChild[0]); /* parent */
    	close(toParent[1]);
	// Creating variables needed for both parent and child process 
        int multiplicand;
        int multiplier;
        int result_p;
	
	//Take in the multiplicand 
        printf("Multiplicand: ");
        scanf("%d", &multiplicand);// scan ithe user input into multiplicand 
        //Write the multiplicand to the pipe - child
        write(toChild[1], &multiplicand, sizeof(multiplicand));
        //Take in the multiplier 
        printf("Multiplier: ");
	// scan the user input into multiplier 
        scanf("%d", &multiplier);
        //Write the multiplier to the pipe - child 
        write(toChild[1], &multiplier, sizeof(multiplier));
        //Read back the answer from the other pipe (result)  
        read(toParent[0],&result_p,sizeof(result_p));
        //Display the result
        printf("Result: %d\n\n", result_p);
      }// end for loop
    }// end else loop
  //puts(ibuf);
  return 0;
}

