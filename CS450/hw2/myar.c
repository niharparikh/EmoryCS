// THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
// A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

#include "myar.h"

int main (int argc, char **argv) {
	
	if(argc <= 2){
		printf("Not enough arguments.\n");
		exit(0);
	}

	char key = argv[1][0];

	if (argc > 3) {
		file_count = argc - 3;
		files = &argv[3];
	}

	ar_name = argv[2];
	ar_fd = open(ar_name, O_RDWR);

	switch (key) {
		case 'q':	append();			break;
		case 'x':	extract();			break;
		case 't':	print_concise();	break;
		case 'A':	appendCD();			break;
		default:	printf("Please enter a key."); exit(0);
	}
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// Main functions
void append () {
	
	// Make sure there are are files to add
	if (file_count <= 0) {
		printf("No files included in arguments.\n");
		exit(0);
	}

	// Create new archive file
	if (ar_fd < 0) {

		ar_fd = open(ar_name, O_CREAT | O_RDWR, 0666);
		
		// Make sure that the file is in standard archive format
		write(ar_fd, "!<arch>", 7);
	}
	else checkArchiveFormat();

	// Add all named files
	int i = 0;
	for (i = 0; i < file_count; i++) {

		int file_fd; 

		// Create stat struct from file
		int test = stat(files[i], &temp_stat);
		
		hdr_ar hdr;

		if (test < 0) {
			printf("File information could not be retrieved: %s. Continuing to next file.\n", files[i]);
			continue;
		}
			
		hdr = populateHeader(files[i], &temp_stat);
		writeHeader(ar_fd, &hdr);

		// Create optimal buffer
		char* buffer2[temp_stat.st_size];
		
		// Write content to archive file
		file_fd = open(files[i], O_RDONLY);
		int check = 0, content_size = temp_stat.st_size;
		check = read(file_fd, buffer2, content_size);
		
		if (check < 0) {
			printf("Error reading file.\n");
		}

		write(ar_fd, buffer2, check);

		close(file_fd);
		
	}	

	close(ar_fd);
	// printf("Appended named files to archive.\n");
}

void appendCD () {

	// Create new archive file if specified one does not exist
	if (ar_fd < 0) {

		ar_fd = open(ar_name, O_CREAT | O_RDWR, 0666);
		
		// Make sure that the file is in standard archive format
		write(ar_fd, "!<arch>", 7);
	}
	else checkArchiveFormat();

	char* temp_name;

	// Open directory and read first file
	DIR *cd = opendir("./"); 
	struct dirent *cf;
	cf = readdir(cd);
	
	// Add files to archive	
	while (cf != NULL) {
			
		temp_name = cf->d_name;

		// Create stat struct from file
		int file_fd; 
		int test = stat(temp_name, &temp_stat);

		if (test < 0) {
			printf("File information could not be retrieved: %s. Continuing to next file.\n", temp_name);
			cf = readdir(cd);
			continue;
		}

		// Check if the file is the archive file & exclude all non-regular types of files
		if (strcmp(ar_name, temp_name) == 0 || cf->d_type != DT_REG) {
			cf = readdir(cd);
			continue;
		}
		
		hdr_ar hdr;
			
		// Update archive file with header information
		hdr = populateHeader(temp_name, &temp_stat);
		writeHeader(ar_fd, &hdr);

		// Create optimal buffer
		char* buffer2[temp_stat.st_size];

		// Write content to archive file
		file_fd = open(temp_name, O_RDONLY);
		int check = 0, content_size = temp_stat.st_size;
		check = read(file_fd, buffer2, content_size);
		
		if (check < 0) {
			printf("Error reading file.");
		}

		write(ar_fd, buffer2, check);

		close(file_fd);
		
		// Iterate to next file
		cf = readdir(cd);
	}
	
	closedir(cd);

	close(ar_fd);

	// printf("Appended current directory to archive.\n");
}

void extract () {
	
	// Make sure there are files to extract
	if (file_count <= 0) {
		printf("No files included in arguments.\n");
		exit(0);
	}

	// Make sure the archive exists
	if (ar_fd < 0) {
		printf("Archive does not exist.\n");
		exit(0);
	}

	checkArchiveFormat();

	int ar_index;
	int temp_fd; 
	hdr_ar hdr;

	struct utimbuf time;

	while (retrieveHeader(&hdr) != NULL) {
		
		// Find index of file in args
		int i = 0;
		for (i = 0; i < file_count; i++) {
			
			if (strcmp(hdr.file_name, files[i]) == 0) {

				// Create new file
				temp_fd = open(hdr.file_name, O_CREAT | O_TRUNC | O_RDWR, 0666);

				// Create stat struct to get file details
				stat(hdr.file_name, &temp_stat);
				hdr.block_size = temp_stat.st_blksize;

				// Add back content
				recreateContent(ar_fd, temp_fd, hdr.size, hdr.block_size);
				close(temp_fd);

				// Restore timestamps
				time.modtime = hdr.timestamp;
				time.actime = hdr.timestamp;
				utime(hdr.file_name, &time);

				// Restore permissions
				chmod(hdr.file_name, hdr.mode & ~umask(0));
			}
			else lseek(ar_fd, hdr.size, SEEK_CUR);
		}

	}

	close(ar_fd);

	// printf("Extracted named files.\n");
}

void print_concise () {
	
	// Check if archive exists.
	if (ar_fd < 0) {
		printf("Archive was not found.\n");
		exit(0);
	}
	
	checkArchiveFormat();

	hdr_ar hdr;
	
	while (retrieveHeader(&hdr) != NULL) {
		
		printf("%s\n", hdr.file_name);
	
		// Go to next block
		lseek(ar_fd, hdr.size, SEEK_CUR);
	}
}


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// Repeated Calls

void checkArchiveFormat () {
	
	read(ar_fd, buffer, 7);
	
	char* test = "!<arch>";
	
	// Check for required string
	int i = 0;
	for (i = 0; i < 7; i++) {
		if (buffer[i] != test[i]) {
			printf("%s is not the standard archive format.\n", ar_name);
			exit(0);
		}
	}

}

hdr_ar* retrieveHeader (hdr_ar *hdr) {
	
	int test = read(ar_fd, buffer, hdr_len);

	// Reached end of the file
	if (test != hdr_len) {
		return NULL;
	}

	// Store first line  of header details in hdr_ar struct from buffer
	sscanf(buffer, "\n%16s%12ld%6d%6d%8o%10d`\n", 
		hdr->file_name, &hdr->timestamp, &hdr->uid, 
		&hdr->gid, &hdr->mode, &hdr->size
	);

	return hdr;

}

void writeHeader (int fd, hdr_ar *hdr) {
	
	int i = 0;

	// Write header details to buffer
	sprintf(buffer, "\n%-16s%-12ld%-6d%-6d%-8o%-10d`\n",
		hdr->file_name, hdr->timestamp, hdr->uid, 
		hdr->gid, hdr->mode, hdr->size
	);

	// Move to the end of the file and then write
	lseek(fd, 0, SEEK_END);
	write(fd, buffer, hdr_len);

}

hdr_ar populateHeader (char* file_name, struct stat *st) {
	
	hdr_ar hdr;
	
	// Add file name to hdr_ar struct
	int i;
	for(i = 0; i < offset_timestamp; i++) {
		if (file_name[i] == '\0') break;
		hdr.file_name[i] = file_name[i];
	}
	hdr.file_name[i] = '\0';

	// Add other file elements to hdr_ar struct
	hdr.timestamp = st->st_mtime;
	hdr.uid = st->st_uid; 	
	hdr.gid = st->st_gid; 
	hdr.mode = st->st_mode;	
	hdr.size = st->st_size;
	hdr.block_size = st->st_blksize;

	return hdr;

}

void recreateContent (int source, int destination, int size, int block_size) {
	
	char buffer2[block_size]; 
	int offset, end;

	// Get tripped up by size vs block size, so just use the smaller		
	while (size > 0) {
		if (size > block_size) end = block_size; 
		else end = size;

		offset = read(source, buffer2, end);
		write(destination, buffer2, offset);
		size -= offset;
	}
}


