// THIS IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
// A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

#include <sys/types.h> 
#include <fcntl.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

// char parent[10]; 	/* room for parents pid in ascii */
// char *child[]={"myname=sort","myname=removedups"};   /* child's name */
int status[2];
int pipefd1[2];			
int pipefd2[2];

int main (int argc, char* argv[]) {
	
	int i; 					/* generic counter */
	int pid[2];				/*pids of children */
	int whom;				/* pid of dead child*/
	// int esize;				/* number of env variables */
	// char **newenvp;         /* constructed env pointer */
	

	/* for fun we will build a new environment with
		some extra values */

	// sprintf(parent,"parent=%d",getpid());

		/* how big is the old environment */

	// for (esize=0; envp[esize] != NULL; esize++);

		/* make new envp 2 slots longer */

	// newenvp = ( char **) malloc((esize + 2) * sizeof(char *));
	// newenvp[0] = parent;

	/* newenvp[1] will be set differently for each child */
	// for (i=0; i<=esize; i++) newenvp[i+2]=envp[i];


	// Set up two pipes
	if (pipe(pipefd1) == -1) {
		perror("pipe");
		exit(10);
	}
	if (pipe(pipefd2) == -1) {
		perror("pipe");
		exit(10);
	}


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* sort child process */

	// Create sort child
	if ((pid[0] = fork()) == -1) {
		perror("fork");
		exit(0);
	}
	else if (pid[0] == 0) {

		// Name the child
		// newenvp[1] = child[0];
		// sleep(getpid() %4); 	/* random wait for some drama*/

		// Not using output pipe 1
		close(pipefd1[1]); 

		// Not using input pipe 2
		close(pipefd2[0]);

		// Redirect input pipe 1 as stdin
	  	dup2(pipefd1[0], 0); 

	  	// Redirect output pipe 2 as stdout
	  	dup2(pipefd2[1], 1);

	  	// Execute sort
	  	execl("/usr/bin/sort", "", NULL);

	}


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* removedups child process */

	// Create removedups child
	if ((pid[1]=fork()) == -1) {
		perror("fork");
		exit(1);
	}
	else if (pid[1] == 0) {

		// Name the child
		// newenvp[1] = child[1];
		// sleep(getpid() %4); 	/* random wait for some drama*/
		
		// Not using pipe 1
		close(pipefd1[0]); 
		close(pipefd1[1]); 

		// Not using output pipe 2
		close(pipefd2[1]);

		// Using input pipe 2
		FILE* input_stream = fdopen(pipefd2[0], "r");

		char c;							/* char to read from stdin */
		char word_current[30];			/* store current word */
		char word_previous[30];			/* store last word */
		int char_count = 0; 			/* count chars in current word */
		int duplicate_count = 1;		/* count duplicate words */
		int eof_flag = 0;				/* check EOF */

		memset(word_previous, '\0', 30);

		while (eof_flag == 0) {
			
			if((c = fgetc(input_stream)) == EOF) eof_flag = 1;

			if (eof_flag) printf("%5d %s\n", duplicate_count, word_current);

			if (c == '\n' && eof_flag == 0) {
				
				int i, j, k; 						/* generic iterator */
				int match_count = 0;

				// Clear out current chars from last word
				for (i = char_count; i < 30; i++) {
					word_current[i] = '\0';
				}

				// Find if current matches previous word
				for (j = 0; j < char_count; j++) {
					if (word_current[j] == word_previous[j]) match_count++;
				}

				// If so, iterate duplicate count, otherwise print out previous word (there will be no more matches)
				if (match_count == char_count) duplicate_count++;
				else if (word_previous[0] != '\0') {
					printf("%5d %s\n", duplicate_count, word_previous);
					duplicate_count = 1;	
				}

				// Copy current word into previous word
				for (k = 0; k < 30; k++) {
					word_previous[k] = word_current[k];
				}

				char_count = 0;
			}
			else {
				// Add chars to current word
				word_current[char_count] = c;
				char_count++;	
			}
		}
		fclose(input_stream);
		exit(0);
	  	
	}



/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Parent process */
	
	char c; 						/* hold char read from stdin */
	int count = 0;					/* count length of word */
	char word[31]; 					/* hold word plus new line char */
	int case_offset = 'a' - 'A';	/* find ASCII separation between upper and lower case */
	int eof_flag = 0;				/* check EOF */
	
	// Not using input pipe 1
	close(pipefd1[0]); 

	// Not using input pipe 2
	close(pipefd2[0]); 

	// Not using output pipe 2
	close(pipefd2[1]);

	// Using output pipe 1
	FILE* output_stream = fdopen(pipefd1[1], "w");

	while (eof_flag == 0) {

		// Set flag
		if ((c = fgetc(stdin)) == EOF) eof_flag = 1;
		
		// Adjust for offset
		if (c >= 'A' && c <= 'Z') c += case_offset;

		// Add to word
		if (c >= 'a' && c <= 'z') {
			word[count] = c;
			count++;
		}
		else {
			if (count >= 3 && count <= 30) {
				word[count] = '\n';
				for (i = 0; i <= count; i++) fputc(word[i], output_stream);
			}
			count = 0;
		}

		if (count > 30) {
			word[30] = '\n';
			for (i = 0; i <= 30; i++) fputc(word[i], output_stream);
			count = 0;
			while ((c = fgetc(stdin)) != EOF) {
				if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
					continue;
				}
				else break;
			}
		}
	}
	// Close out pipe to give EOF
	fclose(output_stream);

	// Wait for children
	for (i = 0; i <= 1; i++) {

		if ((whom = wait(&status[i])) == -1) {
			perror("wait");
			exit(i);
		}
		
		// if (whom == pid[0]) printf("sort died with status=%x\n",status);
		// else if (whom == pid[1]) printf("Alas poor removedups died with status=%x\n",status);
		// else printf("Beats me who died, his pid is=%d",whom);

	}

}