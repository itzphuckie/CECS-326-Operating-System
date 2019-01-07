#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main () {
	int myqueue;
	int myqueueSender;
	key_t mykey;
	int status;
	int multiplicand;
	int multiplier;
	int product;

	struct Mybuf {
		long mtype;
		int mint;
	};

	struct Mybuf buf;
	struct Mybuf bufSender;
	mykey = ftok( "sndmes.c" , 'a' );

	myqueue = msgget(mykey, IPC_CREAT | 0600 );
	myqueueSender = msgget(mykey, IPC_CREAT | 0600);
	if ( -1 == myqueue) {
		printf("error in msgget");
		return 1;
	}
	
	/* no flags so no special instructions */
	for(int i = 0; i < 5; i++){
		status = msgrcv(myqueue, &buf, sizeof(buf), 0, 0);
		multiplicand = buf.mint;
	
		status = msgrcv(myqueue, &buf, sizeof(buf), 0, 0);
		multiplier = buf.mint;

		if ( -1 == status) {
			printf("error in msgrcv");
			return 1;
		}
	
		product = multiplicand*multiplier;
		bufSender.mint = product;
		msgsnd(myqueueSender, &bufSender, sizeof(bufSender), 0);
   	}
}
