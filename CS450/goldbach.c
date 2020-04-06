/* 
THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh
*/

/* Programs works until input of 1368. At 1369 it breaks, can't wrap my head around why, as that is randomly with integer 22 inside of segment 1. 
If you find the solution, please let me know. */
	
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct _seg { 
    int  bits[256];
    struct _seg  *next,*prev;        
      }seg  ;

#define BITSPERSEG  (8*256*sizeof(int))
seg *previous_seg;
int previous_j = 0;
int right_seg_number = 0;

double sqroot(int square)
{
    double root=(double)square/3;
    int i;
    if (square <= 0) return 0;
    for (i=0; i<100; i++)
        root = (root + square / root) / 2;
    return root;
}

seg * whichseg (int j, seg *head) {

	seg *right_seg;

	// Start from head
	right_seg = head;

	// Check last segment
	if (j >= previous_j && previous_seg != NULL) {
		right_seg = previous_seg;
		j = (j - previous_j) + 1;
	} 
	
	// Find segment number for j
	int i;
	right_seg_number = (j-2)/16384;

	// Iterate to right segment
	for (i=1;i<=right_seg_number;i++) {
		right_seg = right_seg->next;
	}

	// Set last segment
	previous_seg = right_seg;
	previous_j = j;

	return right_seg;
}

int whichint (int j) {

	// Find position within array
	j = ((j-2)%16384)/64;
	//printf("%d\n", j);
	return j;

}

int whichbit (int j) {

	// Find position within int
	j = ((j-3)/2)%32;
	//printf("%d\n", j);

	return j;

}

void marknonprime (int j, seg *head) {
	
	// Find right segment
	seg *right_seg;
	right_seg = whichseg(j, head);
	
	// Find right int & bit
	int right_int, right_bit;
	right_int = whichint(j);
	right_bit = whichbit(j);

	//printf("seg: %d, int: %d, bit: %d\n", right_seg_number, right_int, right_bit);

	// Mark bit
	right_seg->bits[right_int] |= (1 << right_bit);

}

// Used to test, unnecessary
int testbit (int j, seg *head) {
	seg *right_seg;
	right_seg = whichseg(j, head);
	
	int right_int, right_bit;
	right_int = whichint(j);
	right_bit = whichbit(j);
	if((1 << right_bit) & right_seg->bits[right_int]) return 1;
	else return 0;
}

void main(int argc, char *argv[]) {

	seg *head, *pt, *pt_start;
	int	 i = 0, j = 0;
	int howmany = 0, howmany_odds = 0, howmany_seg = 0;
	double end_sieve = 0;

	// Only takes command line arguments
	if (argc == 2) sscanf(argv[1],"%d",&howmany);
	else {
		printf("Please input an integer as a command line argument.\n");
		exit(0);
	}

	// Finds number of odd values <= entered value
	if(howmany % 2 == 0) howmany_odds = (howmany / 2) - 1;
	else howmany_odds = howmany / 2;
	howmany_seg = (howmany_odds + BITSPERSEG - 1) / BITSPERSEG; //Only odds
	
	// Initializing space for segments
	head = ( seg * ) malloc(sizeof(seg));
	pt = head;
	for(j=0; j < 256; j++) pt->bits[j] = 0;
	for (i=1;i<howmany_seg;i++) { 
		// Initial with 0's
		for(j=0; j < 256; j++) pt->bits[j] = 0;
		// Create next segment
		pt->next = (  seg *) malloc(sizeof (seg)); 
		pt=pt->next;
	}

	printf("Done allocating %d segments.\n\n",howmany_seg);

	// Calculated upper bound for sieve
	end_sieve = sqroot(howmany);
	// Starting # of primes as number of odd numbers
	int count_primes = 0;
	
	pt = head;
	pt_start = head;
	int real_int = 3, bit_count_start = 0, int_count_start = 0, real_int2 = 3;
	int bit_count = 0, int_count = 0;
	
	// Looping through array to mark non-primes
	for(real_int = 3; real_int <= end_sieve; real_int+=2) {
		// Setting int2 to equal iterating int
		real_int2 = real_int;
		//printf("Start Int: %d\n", real_int2);
		// Testing iterating int to see if it is prime
		if((1 << bit_count_start) & pt_start->bits[int_count_start]) {
			
			// If so, iterate bit_count, and loop to next int
			bit_count_start++;
			
			// Check for overflow bits and ints
			seg *pt_old;
			int bit_old = 0, int_old = 0;
			bit_old = bit_count_start;
			int_old = int_count_start;
			pt_old = pt;

			if(bit_count_start >= 32) {
				while(bit_old >= 0) {
					if(bit_old - 32 < 0) break;
					bit_old -= 32;
					int_old++;
				}
				bit_count_start = bit_old;
				int_count_start = int_old;
			}
			if(int_count_start >= 256) {
				while(int_old >= 0) {
					if(int_old - 256 < 0) break;
					int_old -= 256;
					pt_old = pt_old->next;
				}
				int_count_start = int_old;
				pt_start = pt_old;
			}
			
			continue;
		}
		else { // If not, mark all multiples non-prime
	
			bit_count = bit_count_start;
			int_count = int_count_start;
			pt = pt_start;
			
			while (real_int2 < howmany) {
				// Break if int2 is greater than N
				if((real_int2 + 2*real_int) > howmany) break;


				real_int2 += 2 * real_int;
				bit_count += real_int;
				
				// Check for overflow bits and ints
				seg *pt_old;
				int bit_old = 0, int_old = 0;
				bit_old = bit_count;
				int_old = int_count;
				pt_old = pt;

				if(bit_count >= 32) {
					while(bit_old >= 0) {
						if(bit_old - 32 < 0) break;
						bit_old -= 32;
						int_old++;
					}
					bit_count = bit_old;
					int_count = int_old;
				}
				if(int_count >= 256) {
					while(int_old >= 0) {
						if(int_old - 256 < 0) break;
						int_old -= 256;
						pt_old = pt_old->next;
					}
					int_count = int_old;
					pt = pt_old;
				}

				// Check if already marked non-prime, continue if so
				if((1 << bit_count) & pt->bits[int_count]) {
					continue;
				} else {}

				// Mark bit non-prime
				pt->bits[int_count] |= (1 << bit_count);

			}
			
		}

		// Iterating bit_count to next int
		bit_count_start++;

		seg *pt_old;
		int bit_old = 0, int_old = 0;
		bit_old = bit_count_start;
		int_old = int_count_start;
		pt_old = pt_start;

		// Check for overflow bits and ints
		if(bit_count_start >= 32) {
			while(bit_old >= 0) {
				if(bit_old - 32 < 0) break;
				bit_old -= 32;
				int_old++;
			}
			bit_count_start = bit_old;
			int_count_start = int_old;
		}
		if(int_count_start >= 256) {
			while(int_old >= 0) {
				if(int_old - 256 < 0) break;
				int_old -= 256;
				pt_old = pt_old->next;
			}
			int_count_start = int_old;
			pt_start = pt_old;
		}
	}

	
	// Check bits to count number of primes
	int x = 0, y = 0, z = 0, count_p;
	count_p = 3;
	pt = head;
	for (x=0; x<howmany_seg; x++) {
		for(y=0; y<256; y++) {	
			for(z=0; z<32; z++) {
				
				if(count_p > howmany) break;
				if(((1 << z) & pt->bits[y]) == 0) count_primes++;
				else {}
				count_p += 2;
				
			}
			if(count_p > howmany) break;
		}
		if(count_p > howmany) break;  
		pt=pt->next;
	}

	printf("The number of odd primes less than or equal to %d is: %d.\n\n", howmany, count_primes);

 	printf("Please enter even integers less than %d:\n", howmany);

	int bit_count_in = 0, bit_count_kin = 0, int_count_in = 0, int_count_kin = 0;
	int best_sol_in = 0, best_sol_kin = 0;
	int in, kin;

	// Read in inputs until EOF
	while(!feof(stdin)) {
		
		// Take in k from stdin
		int k;
		scanf("%d",&k);
		
		int count_sums = 0;
		in = 3;
		kin = k - in;
		seg *pt_in;
		seg *pt_kin;

		// Find initial coordinates for i & k-i
		pt_in = whichseg(in, head);
		pt_kin = whichseg(kin, head);
		int_count_in = whichint(in);
		int_count_kin = whichint(kin);
		bit_count_in = whichbit(in);
		bit_count_kin = whichbit(kin);

		// Loop through i until k/2
		while(in <= k/2 && kin > in) {

			// Check i to see if prime, if not, count the solution
			if((1 << bit_count_in) & pt_in->bits[int_count_in]) {}
			else {
				if((1 << bit_count_kin) & pt_kin->bits[int_count_kin]) {}
				else {
					count_sums++;
					best_sol_in = in;
					best_sol_kin = kin;
				}
			}

			// Iterate bit_count for both i and k-i
			bit_count_in += 1;
			in += 2;
			bit_count_kin -= 1;
			kin -= 2;

			if(in > k/2 || kin <= in) break;
			else {}

			// Check for overflow bits and ints
			seg *pt_old;
			int bit_old = 0, int_old = 0;
			bit_old = bit_count_in;
			int_old = int_count_in;
			pt_old = pt_in;

			if(bit_count_in >= 32) {
				while(bit_old >= 0) {
					if(bit_old - 32 < 0) break;
					bit_old -= 32;
					int_old++;
				}
				bit_count_in = bit_old;
				int_count_in = int_old;
			}
			if(int_count_in >= 256) {
				while(int_old >= 0) {
					if(int_old - 256 < 0) break;
					int_old -= 256;
					pt_old = pt_old->next;
				}
				int_count_in = int_old;
				pt_in = pt_old;
			}

			bit_old = bit_count_kin;
			int_old = int_count_kin;
			pt_old = pt_kin;

			if(bit_count_kin >= 32) {
				while(bit_old >= 0) {
					if(bit_old - 32 < 0) break;
					bit_old -= 32;
					int_old++;
				}
				bit_count_kin = bit_old;
				int_count_kin = int_old;
			}
			if(int_count_kin >= 256) {
				while(int_old >= 0) {
					if(int_old - 256 < 0) break;
					int_old -= 256;
					pt_old = pt_old->next;
				}
				int_count_kin = int_old;
				pt_kin = pt_old;
			}

			
		}
		printf("Number of solutions: %d\n", count_sums);
		printf("Largest solution: %d + %d\n\n", best_sol_in, best_sol_kin);
		
		// Clear inputs
		count_sums = 0;
		int_count_in = 0;
		int_count_kin = 0;
		bit_count_in = 0;
		bit_count_kin = 0;
		best_sol_in = 0;
		best_sol_kin = 0;
		
	} 


}
