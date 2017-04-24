#include "header.h"

/**
 * Get input from the keyboard and put it into a 
 * buffer.  Only accept 80 characters max.
 */
int get_data(char* buffer, int length) {

	int overflow_flag = 0;

	/* Clear buffer and reset pointer. */
	bzero(buffer, length);
	fgets(buffer, length, stdin);
	
	/* Read in and get rid of extra characters. */
	if(buffer[strlen(buffer) - 1] != '\n'){
		while(fgetc(stdin) != '\n');
		
		if(!overflow_flag) {
			overflow_flag = 1;
		}
	}
	
	buffer[strlen(buffer) - 1] = '\0';
	
	return overflow_flag;
}

/**
 * Clears the buffer and resets the token.
 */
void reset_token(char* buff) {
	bzero(buff, sizeof(buff));
	
	buff[0] = SYN;
	buff[1] = SYN;
	buff[2] = DLE;
	buff[3] = ETX;
	buff[4] = '\0';
}

/**
 * Fills the frame with data specified by the user.
 */
void fill_frame(char* frame, char machine_id, char* data) {

	frame[0] = SYN;
	frame[1] = SYN;
	frame[2] = DLE;
	frame[3] = STX;
	frame[4] = machine_id;
	frame[5] = data[0];
	frame[6] = '\0';
	strcat(frame, data + 2);
	
	int length = strlen(frame);
	frame[length] = DLE;
	frame[length + 1] = ETX;
	frame[length + 2] = '\0';
}
