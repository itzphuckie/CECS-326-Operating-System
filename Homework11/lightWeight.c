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
        mykey = ftok("lightWeight.c", 'x');

        // Requesting 1 semaphore
        //semid = semget(mykey, 1, IPC_CREAT | 0600);
       // semctl(semid, 0, SETVAL, 1);

        // Print the semaphore ID
       // printf("Semaphore ID: %d\n", semid);

        // Declare structs to lock and unlock semaphore (intersection)
	static struct sembuf Wait = {0, -2, SEM_UNDO};
        static struct sembuf Signal = {0, 2, SEM_UNDO};
	if((semid = semget(mykey, 1, IPC_CREAT | IPC_EXCL | 0600)) != -1){ 
        	semctl(semid, 0, SETVAL, 5);
	}else{
		semid = semget(mykey, 1, 0600);
	}	
	
	// Print the Semaphore ID 
	printf("Semaphore ID: %d\n", semid);
        
	int counter = 0;	
        for(counter = 0; counter < 5; counter++){
                // Lock 
		semop(semid, &Wait, 1);
		printf("LightWeight Starting\n");
		fflush(stdout);
		sleep(2);
		printf("LightWeight Ending\n");
		fflush(stdout);
		// Releasing Lock 
		semop(semid, &Signal, 1);
		sleep(4);
        }
	// Cleaning up the semaphore
	semctl(semid, 0, IPC_RMID, 0);
        return 0;
}

