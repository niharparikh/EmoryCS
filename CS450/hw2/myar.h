// THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
// A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

#include <stdio.h>
#include <stdlib.h>
#include <utime.h>
#include <time.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <string.h>

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

#ifndef DEFINE_CONST

#define hdr_len 61

#define offset_timestamp 17

#define buffer_len 256

#endif

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

#ifndef DEFINE_VAR

static int file_count;
static char** files;

static int ar_fd;
static char* ar_name;

struct stat temp_stat;
char buffer[buffer_len];

#endif

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

#ifndef DEFINE_DS

typedef struct _hdr_ar {
	char file_name[offset_timestamp];
	long timestamp;
	int	uid;
	int gid;
	int	mode;
	int block_size;
	int size;
} hdr_ar;

#endif

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// Main functions
extern void append(void);
extern void appendCD(void);
extern void extract(void);
extern void print_concise(void);

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// Repeated calls
extern void checkArchiveFormat(void);
extern hdr_ar* retrieveHeader(hdr_ar*);
extern hdr_ar populateHeader(char*, struct stat*);
extern void writeHeader(int, hdr_ar*);
extern void recreateContent(int, int, int, int);
