/*
    THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
    A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Yu-Hsin (Henry) Chen
*/
    
#include "ds.h"

void logProcess(int);
void logPerfectNumber(int);

int main(int argc, char** argv){
	init();

	while(true){
      msgrcv(msg_id, &message, sizeof(message.data), -2, 0);
      switch(message.type){
      	case 1: logProcess(message.data); break;
      	case 2: logPerfectNumber(message.data); break;
      }
   	}

	return 0;
}

void logProcess(int pid){
	int idx;
	for(idx = 0; idx < PROCESS_TABLE_SIZE; idx++){
		if(SHM->process[idx][0] == 0){
			SHM->process[idx][0] = pid;
			message.type = 3; message.data = idx;
			msgsnd(msg_id, &message, sizeof(message.data), 0);
			return;
		}
	}

	/* If the table is full, kill the process */
	perror("Process table is full."); kill(pid, SIGINT);
}

void logPerfectNumber(int num){
	int idx, entry;
	for(idx = 0; idx < PERFECT_NUM_SIZE; idx++){
		entry = SHM->perfectNum[idx];
		if(entry == 0){
			SHM->perfectNum[idx] = num;
			return;
		}
		else if(entry == num) 	return;
	}

	/* If the table is full, report error */
	perror("Perfect number table is full.");
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

		/* Init manage Id */
		SHM->manageId = (int)getpid();

		int i, j;
		/* Init bit map */
		for(i = 0; i < BITMAP_INT_SIZE; i++) 	SHM->bitmap[i] = 0;
		/* Init perfect number */
		for(i = 0; i < PERFECT_NUM_SIZE; i++) 	SHM->perfectNum[i] = 0;
		/* Init process table */
		for(i = 0; i < PROCESS_TABLE_SIZE; i++)
			for(j = 0; j < 4; j++) SHM->process[i][j] = 0;
	}
}

void cleanup(void){
	/* Send interrupt signal to all process */
	int i; int pid;
	for(i = 0; i < PROCESS_TABLE_SIZE; i++){
		if( (pid = SHM->process[i][0]) != 0)
			kill((pid_t)pid, SIGINT);
	}

	/* Remove message queue */
	if(msgctl(msg_id, IPC_RMID, null) == -1){
		perror("msgctl"); exit(-1);
	}
	sleep(5);
	
	/* Remove shared memory */
	if(shmdt((void*)SHM) == -1){
		perror("shmdt"); exit(-1);	
	}
	else if(shmctl(shm_id, IPC_RMID, null) == -1){
		perror("shmctl"); exit(-1);
	}
}