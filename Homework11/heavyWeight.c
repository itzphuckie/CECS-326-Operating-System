#include <stdio.h> /* Needed for printf.*/
#include <unistd.h>/*Needed for fork and exist*/
#include <sys/wait.h> /*Needed for wait*/
#include <stdbool.h> /* Needed for boolien */
#include <sys/types.h> /* Needed for semaphore */
#include <sys/ipc.h> /* Needed for semaphore */
#include <sys/sem.h> /* Needed for semaphore */

int main(int argc, char *argv[]){

        // Creating semaphore
	key_t mykey;
	int semid;
	mykey = ftok("heavyWeight.c", 'x');

        // Declare structs to lock and unlock semaphore (intersection)
	static struct sembuf Wait = {0, -3, SEM_UNDO};
        static struct sembuf Signal = {0, 3, SEM_UNDO};
	if((semid = semget(mykey, 1, IPC_CREAT | IPC_EXCL | 0600)) != -1){ 
        	semctl(semid, 0, SETVAL, 5);
	}else{
		semid = semget(mykey, 1, 0600);
	}
		
	// Print the semaphore ID 
	printf("Semaphore ID: %d\n", semid);	

        int counter = 0;
        for(counter = 0; counter < 5; counter++){
                // Locking 
		semop(semid, &Wait, 1);
		printf("HeavyWeight Starting\n");
		fflush(stdout);
		// Sleeping for 4 seconds 
                sleep(4);
                printf("HeavyWeight Ending\n");
		fflush(stdout);
                // releasing the lock 
		semop(semid, &Signal, 1);
		sleep(8);       
	 }
	semctl(semid, 0, IPC_RMID, 0);

 return 0;
}
