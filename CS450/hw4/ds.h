/*
    THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
    A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Yu-Hsin (Henry) Chen
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifndef DEFINE_CONST

static const key_t KEY = (key_t)28096;

#define BITMAP_BIT_SIZE 	33554432
#define BITMAP_INT_SIZE		BITMAP_BIT_SIZE/32+1
#define PERFECT_NUM_SIZE 	20
#define PROCESS_TABLE_SIZE 	20

#define null NULL
typedef enum{false, true} boolean;

#define DEFINE_CONST
#endif

#ifndef DEFINE_DS

typedef struct _request {
	/* 	
		1: log process, 
		2: log perfect number,
		3: return process table index
	*/
	long type;			
	int  data;
} Request;

typedef struct _sharedmem {
	int manageId;
	int bitmap[BITMAP_INT_SIZE];
	int perfectNum[PERFECT_NUM_SIZE];
	int process[PROCESS_TABLE_SIZE][4];
} SharedMem;

#define DEFINE_DS
#endif

#ifndef DEFINE_VAR

static int msg_id;
static int shm_id;
static SharedMem *SHM;
static Request message;

#define DEFINE_VAR
#endif

extern void signal_handler(int);
extern void init(void);
extern void cleanup(void);

