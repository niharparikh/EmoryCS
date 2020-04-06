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
	// printf("%d\n", size);

	sid = shmget(key, size, IPC_CREAT | 0660);
	printf("sid: %d\n", sid);
	
	struct shared *pt; 
	if((pt = (struct shared *) shmat(sid, 0, 0)) == (struct shared *)(-1)) {
		printf("shmat error\n");
		perror("shmat");
		exit(0);
	} 

	int i;
	for(i = 0; i < (sizeof(pt->bitmap)/sizeof(pt->bitmap[0])); i++) pt->bitmap[i] = 0;
	int t, u;
	for(t = 0; t < 20; t++) for(u = 0; u < 4; u++) pt->processes[t][u] = 0;

	//Test
	// pt->summary[0] = 5;

	struct msgbuf {
	    long mtype;
	    int mcontents;
	};
	
	struct msgbuf question;
	int msgsize = sizeof(question.mcontents);

	int msgid;
	msgid = msgget(key, IPC_CREAT | 0660);

	long msg_type;
	
	
	while(1) {
		
		if((msgrcv(msgid, &question, msgsize, 0, IPC_NOWAIT)) == -1) {
			if(errno == ENOMSG) continue;
			else {
				printf("msgrcv error\n");
				perror("msgrcv");
				exit(0);
			}
		}
		msg_type = question.mtype;

		if(msg_type == 2) {

			int k = 0;
			while(k < 20) {
				if(pt->processes[k][0] < 1) break;
				if(k == 19) {
					k += 1; 
					break;
				}
				k++;
			}

			if(k == 20) {
				printf("Cannot account for any more processes.\n");
				break;
			}

			pt->processes[k][0] = question.mcontents;
			pt->processes[k][1] = 0;
			pt->processes[k][2] = 0;
			pt->processes[k][3] = 0;

			printf("%s\n", "Received compute create");

			struct msgbuf response;
			response.mtype = 3;
			response.mcontents = k;
			printf("%s\n", "before");
			if((msgsnd(msgid, &response, msgsize, 0)) == -1) {
				perror("msgsnd");
				exit(0);
			}
			else printf("%s\n", "Sent Message");

		}

		if(msg_type == 4) {
			int y;
			for(y = 0; y < 20; y++) {
				if(y == 0) {
					pt->perf[y] = question.mcontents;
					break;
				}
			}
			printf("Found perfect number: %d\n", question.mcontents);
		}

		// if(msg_type == 5) {
		// 	int row = question.mcontents;
		// 	pt->processes[row][0] = 0;
		// 	pt->processes[row][1] = 0;
		// 	pt->processes[row][2] = 0;
		// 	pt->processes[row][3] = 0;
		// }
		
	}
    
}