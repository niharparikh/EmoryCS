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

int whichint (int j) {
	j = (j-2)/32;
	return j;
}

int whichbit (int j) {
	j = (j-2)%32;
	return j;
}

struct shared {
	int bitmap[256];
	int perf[20];
	int processes[20][4];
	int summary[3];
}shared;

int main(int argc, char *argv[]) {

	key_t key = 96224;

	int sid;
	sid = shmget(key, sizeof(struct shared), IPC_CREAT | 0660);
	printf("sid: %d\n", sid);

	struct shared *pt; 
	if((pt = (struct shared *) shmat(sid, 0, 0)) == (struct shared *)(-1)) {
		perror("shmat");
		exit(0);
	} 

	struct msgbuf {
	    long mtype;
	    int mcontents;
	};

	struct msgbuf question;
	int msgsize = sizeof(question.mcontents);
	question.mtype = 2;
	question.mcontents = (int)getpid();
	
	int msgid;
	msgid = msgget(key, IPC_CREAT | 0660);
	msgsnd(msgid, &question, msgsize, 0);

	printf("msgid: %d\n", msgid);

	struct msgbuf response;
	// response = malloc(sizeof(*response));
	int row = 0, i;
	// msgrcv(msgid, &response, msgsize, 3, IPC_NOWAIT);
	while(1) {
		if(msgrcv(msgid, &response, msgsize, 3, 0) == -1) {
			if(errno == ENOMSG) printf("%s", "");
			else {
				printf("msgrcv error\n");
				perror("msgrcv");
				exit(0);
			}
		}
		else {
			printf("Row: %d\n", response.mcontents);
			row = response.mcontents;
			break;
		}
		// i++;
	}

	// Test
	int u, v;
	for(u = 0; u < 20; u++) for(v = 0; v < 4; v++) printf("u: %d, v: %d, value: %d\n", u, v, pt->processes[u][v]);

	int j, sum, n;

	// printf("high\n");

	int start = atoi(argv[1]);
	// printf("%d\n", start);
	// if(start < 2) start = 2;
	n = start;
	int right_int = whichint(n);
	int right_bit = whichbit(n);
	int loop = 0;

	while (1) {
		
		if(loop == 1 && n == start) {
			pt->processes[row][0] = 0;
			pt->processes[row][1] = 0;
			pt->processes[row][2] = 0;
			pt->processes[row][3] = 0;
			exit(0);
			// struct msgbuf quit;
			// quit.mtype = 5;
			// quit.mcontents = row;
			// msgsnd(msgid, &quit, msgsize, 0);
		}

		// Skip checked value
		if((1 << right_bit) & pt->bitmap[right_int]) {
			pt->processes[row][3]++;

			int bit_old = 0, int_old = 0;
			bit_old = right_bit;
			int_old = right_int;
			if(right_bit >= 32) {
				while(bit_old >= 0) {
					if(bit_old - 32 < 0) break;
					bit_old -= 32;
					int_old++;
				}
				right_bit = bit_old;
				right_int = int_old;
			}
			if(right_int >= (sizeof(pt->bitmap)/sizeof(pt->bitmap[0]))) {
				n = 2;
				loop = 1;
				continue;
			}

			n++;
			continue;
		}
		

		// Find perfect number
		sum = 1;
		for(j = 2; j < n; j++) if(!(n%j)) sum+=j;
		if(sum == n) {
			pt->processes[row][1]++;
			printf("%d is perfect\n", n);
			struct msgbuf found;
			found.mtype = 4;
			found.mcontents = n;
			msgsnd(msgid, &found, msgsize, 0);
		}
		
		// Iterate tested
		pt->processes[row][2]++;

		// Set bit as tested
		pt->bitmap[right_int] |= (1 << right_bit);
		
		// Iterate to next bit
		right_bit++;
		int bit_old = 0, int_old = 0;
		bit_old = right_bit;
		int_old = right_int;
		if(right_bit >= 32) {
			while(bit_old >= 0) {
				if(bit_old - 32 < 0) break;
				bit_old -= 32;
				int_old++;
			}
			right_bit = bit_old;
			right_int = int_old;
		}

		// If past end of bitmap, loop around
		if(right_int >= (sizeof(pt->bitmap)/sizeof(pt->bitmap[0]))) {
			n = 2;
			loop = 1;
			continue;
		}

		// printf("bottom\n");
		n++;
	}
	return 0;
    
}

