/*
    THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
    A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Yu-Hsin (Henry) Chen
*/
    
#include "ds.h"

static boolean cleanupAll = false;
void report(void);
int countTested(void);

int main(int argc, char** argv){
	if(argc == 2 && (argv[1][0] == '-' && argv[1][1] == 'k' && argv[1][2] == '\0')){
		cleanupAll = true;
	}
	init(); report(); cleanup();
}

void report(void){
	int i;
	/* Print perfect number found */
	printf("Perfect numbers found:\n");
	for(i = 0; i < PERFECT_NUM_SIZE; i++)
		if(SHM->perfectNum[i] != 0) printf("%d ", SHM->perfectNum[i]);
	printf("\n");

	/* Print total number tested */
	printf("Total number tested: %d\n", countTested());

	/* Print process information */
	for(i = 0; i < PROCESS_TABLE_SIZE; i++){
		if(SHM->process[i][0] != 0)
			printf("Compute process: %-8d\ttested: %-8d\tskipped: %-8d\tfound: %-8d\n", 
				SHM->process[i][0], SHM->process[i][1], SHM->process[i][2], SHM->process[i][3]);
	}
}

int countTested(void){
	int i, sum = 0;
	for(i = 1; i < BITMAP_BIT_SIZE; i++)
		if(SHM->bitmap[i/(sizeof(int)*8)] & (1 << ((sizeof(int)*8-2) - i%(sizeof(int)*8))))
			sum++;
	return sum;
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
	}
}

void cleanup(void){
	if(cleanupAll) 
		kill((pid_t)SHM->manageId, SIGINT);

	/* Detach shared memory */
	if(shmdt((void*)SHM) == -1){
		perror("shmdt"); exit(-1);	
	}
}