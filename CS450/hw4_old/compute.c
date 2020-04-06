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

int main(int argc, char *argv[]) {

	struct shared {
		int bitmap[256];
		int perf[20];
		int processes[20][4];
		int summary[3];
	}shared;

	key_t key = 96224;

	int sid;
	sid = shmget(key, sizeof(struct shared), IPC_CREAT | 0666);

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
	question.mcontents = getpid();
	
	int msgid;
	msgid = msgget(key, IPC_CREAT | 0666);
	msgsnd(msgid, &question, msgsize, 0);

	struct msgbuf response;
	msgrcv(msgid, &response, msgsize, 3, 0);
	printf("Row: %d\n", response.mcontents);

	int j, sum, n;

	// printf("high\n");

	int start = atoi(argv[1]);
	// printf("%d\n", start);
	// if(start < 2) start = 2;
	n = start;
	int right_int = whichint(n);
	int right_bit = whichbit(n);

	while (1) {
		// printf("top\n");
		if((1 << right_bit) & pt->bitmap[right_int]) {
			pt->processes[response.mcontents][3]++;

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
				n = start;
				break;
			}

			n++;
			continue;
		}
		// printf("middle\n");
		sum = 1;
		for(j = 2; j < n; j++) if(!(n%j)) sum+=j;
		if(sum == n) {
			pt->processes[response.mcontents][1]++;
			printf("%d is perfect\n", n);
			struct msgbuf found;
			found.mtype = 4;
			found.mcontents = n;
			msgsnd(msgid, &found, msgsize, 0);
		}
		pt->processes[response.mcontents][2]++;

		pt->bitmap[right_int] |= (1 << right_bit);

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
		if(right_int >= (sizeof(pt->bitmap)/sizeof(pt->bitmap[0]))) {
			n = start;
			break;
		}

		// printf("bottom\n");
		n++;
	}
    
}

