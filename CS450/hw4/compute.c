/*
    THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
    A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Yu-Hsin (Henry) Chen
*/
    
#include "ds.h"

static int PROCESS_TABLE_IDX;

int main(int argc, char** argv){
	if(argc != 2){ 
		perror("Wrong number of arguments: ./compute <beginNum>"); exit(-1);
	}
	else init();

	int i, sum, num = atoi(argv[1]); 
	if(num <= 0){
		printf("Begin number is not a positive interger > 0.\n"); exit(-1);	
	}

	boolean hasTested;
	while(num < BITMAP_BIT_SIZE){
		hasTested = SHM->bitmap[num/(sizeof(int)*8)] & (1 << ((sizeof(int)*8-2) - num%(sizeof(int)*8)));
		if(!hasTested){
			sum = 1;
			for(i = 2; i < num; i++)
				if(num % i == 0) sum += num / i;
			if(sum == num && num != 1){
				SHM->process[PROCESS_TABLE_IDX][3]++;
				message.type = 2; message.data = num;
				msgsnd(msg_id, &message, sizeof(message.data), 0);
			}
			SHM->bitmap[num/(sizeof(int)*8)] |= (1 << ((sizeof(int)*8-2) - num%(sizeof(int)*8)));
			SHM->process[PROCESS_TABLE_IDX][1]++;
		}
		else SHM->process[PROCESS_TABLE_IDX][2]++;
		num++;	
	}
	cleanup(); return 0;
}

void signal_handler(int sig_no){
	switch(sig_no){
		case SIGTERM: 	signal(SIGTERM,  SIG_IGN); cleanup(); exit(0);
	  	case SIGINT: 	signal(SIGINT,  SIG_IGN); cleanup(); exit(0);
	  	case SIGQUIT: 	signal(SIGQUIT, SIG_IGN); cleanup(); exit(0);
	  	case SIGHUP:	signal(SIGHUP,  SIG_IGN); cleanup(); exit(0);
	}
}

void init(void){
	/* Init message queue */
	if ( (msg_id = msgget(KEY, IPC_CREAT | 0660) ) == -1) {
		perror("msgget"); exit(-1);
	}

	/* Init shared memory */
	if ( (shm_id = shmget(KEY, sizeof(SharedMem), IPC_CREAT | 0660))== -1) {
		perror("shmget"); exit(-1);
	}
	else if( (SHM = (SharedMem*)shmat(shm_id, 0, 0)) == (SharedMem*)-1){
		perror("shmat"); exit(-1);	
	}
	else{
		/* Init signal handdler */
		signal(SIGTERM, signal_handler);
		signal(SIGQUIT, signal_handler);
		signal(SIGINT,  signal_handler);
		signal(SIGHUP,  signal_handler);

		/* Request for process table idx */
		message.type = 1; message.data = (int)getpid();
		msgsnd(msg_id, &message, sizeof(message.data), 0);
		msgrcv(msg_id, &message, sizeof(message.data), 3, 0);
		PROCESS_TABLE_IDX = message.data;
	}
}

void cleanup(void){
	/* Remove process entry */
	int i;
	for(i = 0; i < 4; i++)
		SHM->process[PROCESS_TABLE_IDX][i] = 0;

	/* Detach shared memory */
	if(shmdt((void*)SHM) == -1){
		perror("shmdt"); exit(-1);	
	}
}