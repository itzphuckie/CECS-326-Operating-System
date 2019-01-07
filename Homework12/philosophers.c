/* You need to switch from 2 to 5 semaphores.
   Initialize the 5 semaphores to unlocked.
   You still only need two semaphores in the OpList.
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
int main () {
  struct sembuf Wait[5]  = { {0,-1,SEM_UNDO}, {1,-1,SEM_UNDO}, {2,-1,SEM_UNDO},{3,-1,SEM_UNDO}, {4,-1,SEM_UNDO} };
 
 struct sembuf Signal[5] = { {0,1,SEM_UNDO}, {1,1,SEM_UNDO}, {2,1,SEM_UNDO}, {3,1,SEM_UNDO}, {4,1,SEM_UNDO} };
  int ch, i, pid;
  key_t mykey;
  int semid;
  union wait waitstatus;
  struct sembuf OpList[2];

  mykey = ftok("philosophers.c",'a');
  semid = semget(mykey, 5, IPC_CREAT | 0600 );
  // Setting the value for semaphores 
  semctl(semid,0,SETVAL,1);
  semctl(semid,1,SETVAL,1);
  semctl(semid,2,SETVAL,1);
  semctl(semid,3,SETVAL,1);
  semctl(semid,4,SETVAL,1);
	
/*
  if (fork()==0) { //child
    OpList[0] = Wait[0];
    OpList[1] = Wait[1];
    printf("Waiting\n");
    semop(semid,OpList,2);
    printf("Unlocked\n");
  } else { //parent
    sleep(3);
    OpList[0] = Signal[0];
    OpList[1] = Signal[1];
    semop(semid,OpList,2);
    wait3(&ch,0,NULL);
  }
*/
  for (i = 0 ; i < 5 ; i++ )
  {
    pid = fork();
    if (pid == 0) break;
  }
  if (pid == 0)
  {
    pid = getpid();
    /* do the philosopher thing */
    // Initilize 2 philosophers
    int phi_1, phi_2;
   // When the "circle" of philosophers are at the end, it resets 
    for(int i = 0; i < 5; i++){
	if((i+1) > 4){
	    phi_1 = 0;
	}else{
	    phi_1 = i + 1;
	}
	phi_2 = i;
	if (i == 4){
	    phi_2 = phi_1;
	    phi_1 = i;
	}
	// Lock resources while eating 
	semop(semid, &Wait[phi_1],1);
    	semop(semid, &Wait[phi_2],1);
	// Display philosopher and pid ID 
    	printf("Philsosopher %d eating\n", pid);
   	sleep(1);//Eat
	// Display philosopher thinking and pid ID 
	semop(semid, &Signal[phi_1],1);
    	semop(semid, &Signal[phi_2],1);
    	printf("Philosopher %d thinking\n", pid);
    	sleep(4);//Think
    }
    return 0;
  }// end pid == 0 if loop
  else
  {
    for (i = 0 ; i < 5 ; i++){
      wait3(&ch,0,NULL);
    }
    /* remove the semaphore */
    //Remove semaphore
    semctl(semid, 0, IPC_RMID, 0);
    semctl(semid, 1, IPC_RMID, 0);
    semctl(semid, 2, IPC_RMID, 0);
    semctl(semid, 3, IPC_RMID, 0);
    semctl(semid, 4, IPC_RMID, 0);
    return 0;
  }
}
