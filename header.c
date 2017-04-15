#include "header.h"

/**
 * Get input from the keyboard and put it into a 
 * buffer.  Only accept 80 characters max.
 */
void get_input(char* buffer, int length) {

	/* Clear buffer and reset pointer. */
	bzero(buffer, length);
	fgets(buffer, length, stdin);
	
	/* Read in and get rid of extra characters. */
	if(buffer[strlen(buffer) - 1] != '\n'){
		printf("TOO LONG\n");
		while(fgetc(stdin) != '\n');
	}
	
	buffer[strlen(buffer) - 1] = '\0';
	
	return;
}
