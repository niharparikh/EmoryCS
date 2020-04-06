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

		

}