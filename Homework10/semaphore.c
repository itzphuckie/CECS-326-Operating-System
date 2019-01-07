#include <stdlib.h> /* Needed for fork */
#include <stdio.h> /* Needed for printf.*/
#include <unistd.h>/*Needed for fork and exist*/
#include <sys/wait.h> /*Needed for wait*/
#include <stdbool.h> /* Needed for boolien */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */

int main(int argc, char *argv[]){

	// Create a semaphore variable before fork() and initialize it
	key_t mykey;
	int semid;
	mykey = ftok(".cshrc", 'x');
	
	// Requesting 1 semaphore
	semid = semget(mykey, 1, IPC_CREAT | 0600);
	semctl(semid, 0, SETVAL, 1);

	// Print the semaphore ID
	printf("Semaphore ID: %d\n", semid);

	// Declare structs to lock and unlock semaphore (intersection)
	static struct sembuf Wait = {0, -1, SEM_UNDO};
	static struct sembuf Signal = {0, 1, SEM_UNDO};
	
	// Fork a process
	int is_child = fork();
	int counter = 0;
	
	while( counter < 10){
		// Logic for the Child, print N/S
		if( is_child == 0){
			// Lock the intersection
			// Wait fro the car to cross 
			semop(semid, &Wait, 1); 
			printf("N/S car entering intersection \n");
			sleep(1); // The time that takes for car to cross intersection
			printf("N/S car leaving intersection\n");
			// Releasing the lock
			semop(semid, &Signal, 1); // Signaling that car has crossed the intersection 
		}
		// Else move to the logic for parent , not 0, do the same process but prints E/W
		else{
			//Lock the intersection
			semop(semid, &Wait, 1);
			printf("E/W car entering intersection \n");
			sleep(1);
			printf("E/W car leaving intersection \n");
			semop(semid, &Signal, 1);
		}
		
		//Counter increment every time after loop
		counter = counter + 1;
		//printf("Counter", counter); CHECKING IF IT LOOPS
	}
	
	return 0;
}
