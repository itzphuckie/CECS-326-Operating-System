#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main () {
	int myqueue;
	int myqueueReceiver;
	key_t mykey;
	int status;
	int status_multiplicand;
	int status_multiplier;
	int multiplicand;
	int multiplier;
	int product;

	struct Mybuf {
		long mtype;
		int mint;
	};

	struct Mybuf buf;
	struct Mybuf bufReceiver;
	mykey = ftok( "sndmes.c" , 'a' );

	myqueue = msgget(mykey, IPC_CREAT | 0600 );
	myqueueReceiver = msgget(mykey, IPC_CREAT | 0600);

	if ( -1 == myqueueReceiver) {
	  printf("error in msggetRCV");
	  return 1;
	}
	
	if ( -1 == myqueue) {
	  printf("error in msgget");
	  return 1;
	}

	/* no special instructions */
	buf.mtype = 1;
	bufReceiver.mtype = 1;
	/* no flags */
for(int i = 0; i < 5; i++){
	printf("Multiplicand: ");
	scanf("%d", &multiplicand);
	buf.mint = multiplicand;	
	status = msgsnd(myqueue, &buf, sizeof(buf), 0);

	printf("Multiplier: ");
	scanf("%d", &multiplier);
	buf.mint = multiplier;
	status = msgsnd(myqueue, &buf, sizeof(buf), 0);

	if ( -1 == status) {
	  printf("error in msgsnd %s \n", strerror(errno) );
	  return 1;
	}

	msgrcv(myqueueReceiver, &bufReceiver, sizeof(bufReceiver), 0, 0);
	product = bufReceiver.mint;
	printf("Product: %d\n", product);
	}
}
