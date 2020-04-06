/* Program to illustrate the use of traditional  signals on UNIX 
		The program runs a computational loop to 
		compute perfect numbers starting at a fixed
		point.

	A time alarm signal is used to periodically print status
	An interrupt signal is used for status on demand
	A quit signal is used to reset the test interval (or terminate) */

#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <stddef.h>
#include <sys/shm.h>
#include <fcntl.h>

struct shared {
	int bitmap[256];
	int perf[20];
	int processes[20][4];
	int summary[3];
}shared;	

int main() {

	key_t key = 96224;

	int sid;
	int size = sizeof(shared);
	printf("%d\n", size);

	sid = shmget(key, size, IPC_CREAT | 0666);
	printf("sid: %d\n", sid);
	
	struct shared *pt; 
	if((pt = (struct shared *) shmat(sid, 0, 0)) == (struct shared *)(-1)) {
		printf("shmat error\n");
		perror("shmat");
		exit(0);
	} 

	int i;
	for(i = 0; i < (sizeof(pt->bitmap)/sizeof(pt->bitmap[0])); i++) pt->bitmap[i] = 0;

	//Test
	pt->summary[0] = 5;


	struct msgbuf {
	    long mtype;
	    int mcontents;
	};
	
	struct msgbuf question;
	int msgsize = sizeof(question.mcontents);

	int msgid;
	msgid = msgget(key, IPC_CREAT | 0666);


	
	int k = 0;
	
	while(1) {
		
		msgrcv(msgid, &question, msgsize, 2, 0);
		
		pt->processes[k][0] = question.mcontents;
		pt->processes[k][1] = 0;
		pt->processes[k][2] = 0;
		pt->processes[k][3] = 0;

		struct msgbuf response;
		response.mtype = 3;
		response.mcontents = k;
		msgsnd(msgid, &response, msgsize, 0);
		// TODO: find open row, not just next one
		k++;

		// TODO: find out how to get all perfect number messages, not just one
		struct msgbuf found;
		msgrcv(msgid, &found, msgsize, 4, 0); 
		printf("found perfect number: %d\n", found.mcontents);

		if(k == 20) {
			printf("Cannot account for any more processes.\n");
			exit(0);
		}
		
	}
    
}