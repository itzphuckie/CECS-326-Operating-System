#include <stdlib.h> /* Needed fo`r fork */
#include <stdio.h> /* Needed for printf. */
#include <stdbool.h> /* Needed for bool, optional. */
#include <unistd.h> /* Needed for fork and exit. */
//#include <sys/wait.h> /* Needed for avoiding errors. */
#include <pthread.h> /* Needed for thread */
// Global Variables
int sum;
int i;
char input[26];
//sum = 0;
int character, n = 0;


void* ChildThread(void *arg){
	// local - add int i = 0
	for ( i=0; i<=10; i++) {
     	//Check if process is a child
     	 printf("C %c\n", input[i]);
      	sleep(2);
 	 }
}
int main (int argc, char *argv[]){
	// put to sleep for 5 seconds
	printf("Sleeping...\n");
	sleep(5);
 	while((character = getchar()) != '\n' && n<26)
 	 {
 		 input[n] = character;
		  ++n;
 	 }
	
	 pthread_t th;
 	 pthread_attr_t ta;

 	(void) pthread_attr_init(&ta);
	(void) pthread_attr_setdetachstate(&ta, PTHREAD_CREATE_DETACHED);
      	pthread_create(&th, &ta, (void * (*)(void *))ChildThread, NULL);

	for(i=0; i<=10; i++)
   	 {
     		printf("P %c\n", input[i]);
      		sleep(1);
   	 }


// If there is an argument (other than the name of the file being excuted) and you are parent, wait for child "

//if(argc > 1 && is_Child != 0)// || argv[1] == "fork.c")
//{
//	int status;
//	wait3( &status, 0, NULL);
//	return 0 + status;
//}


return 0;
};
