#include "header.h"

int main(int argc, char **argv){

	/************************************* Connect all machines. **************************************/

	/* Check if correct parameters were provided. */
    if (argc != 4) {
        printf("Usage: %s <server IP> <client IP> <machine ID>\n", argv[0]);
        printf("\t\t     <server IP> : The IP address of the current machine.\n");
        printf("\t\t     <client IP> : The IP address of the subsequent machine.\n");
        printf("\t\t     <machine ID>: THe uniqe ID assigned to this machine.\n");
        return -1;
    }
	
	/* Attempt client connection first. */
	int client_fd = Client(argv[2]);
	
	/* Attempt server connection regardless of outcome of client connection. */
	int server_fd = Server(argv[1]);
	
	/* Assign the user specified machine ID. */
	char machine_id = argv[3][0];
	
	/* Keept attempting to connect client until succeeds. */
	while(client_fd <= 0) {
		client_fd = Client(argv[2]);
	}
	
	/****************************** All connected actual operation time. ******************************/
	
	printf("Enter your messages as follows: <machine id> <message>\n");
	
	int num_fds;
	fd_set rset;	/* Declare an fd_set for read descriptors. */
	int is_ready = 0;
	
	char buffsend[89], buffrecv[89], frame[89];

	/* Endless loop for continuous operation. */
	while(1) {
	
		/* Clear all bits in rset, set the standard input bit, and set the socket descriptor bit. */
		FD_ZERO(&rset);
		FD_SET(STDIN_FILENO, &rset);
		FD_SET(server_fd, &rset);
 		num_fds = select((server_fd > STDIN_FILENO ? server_fd : STDIN_FILENO) + 1, &rset, NULL, NULL, NULL);
 		
		/* Select blocks, and n is the number of ready descriptors. */
		if((num_fds == -1) && (errno == EINTR)) /* interruption */
		   continue;
	  	
		/* After this point, handle the ready descriptor(s). */
	  
	  	/* Check for ready data from the keyboard. */
	  	if(FD_ISSET(STDIN_FILENO, &rset)) {
	  	
	  		/* Clear out frame. */
	  		bzero(frame, sizeof(frame));
	  		
	  		/* Get user input from the keyboard. */
			if(get_data(buffsend, 84)) printf("\nMessage too long sending truncated version\n\n");
			
			/* User entered CTRL-P, generate the token. */
			if(buffsend[0] == DLE) {
				char token[88];
				reset_token(token);
				
				/* Write to the receiver. */
				if(write(client_fd, token, sizeof(token)) < 0) ReportError("write error\n");
			}
			
			/* User is attempting to fill the frame but formatted the message wrong. */
			else if(buffsend[1] != ' ') {
			
				printf("\nERROR: Format your messages <machine id> <message>\n");
			
			/* User is attempting to fill the frame and formatted the message correctly. */
			} else {
			
				/* Frame and set the ready flag. */
				fill_frame(frame, machine_id, buffsend);
				is_ready = 1;
			}
			
			/* Decrease the number of ready file descriptors. */
			num_fds--;
	  	}
	 
	  	/* Check for ready data from the communication channel. */
	  	if((num_fds > 0) && (FD_ISSET(server_fd, &rset))) {
	  	
			/* Read data from socket. */
			bzero(buffrecv, sizeof(buffrecv));
			bzero(buffsend, sizeof(buffsend));
			if(read(server_fd, buffrecv, sizeof(buffrecv)) < 0) ReportError("read error\n");
			
			/* DLE-STX received.  There is data in the frame. */
			if(buffrecv[2] == DLE && buffrecv[3] == STX) {
			
				/* The data is addressed to this machine. Extract the data. */
				if(buffrecv[5] == machine_id) {
					buffrecv[strlen(buffrecv) - 2] = '\0';
					printf("From %c: %s\n", buffrecv[4], buffrecv + 6);
					reset_token(buffsend);
			
				/* The data was sent by this machine but the destination was not found. */
				} else if(buffrecv[4] == machine_id) {
					printf("Machine %c does not exist in this network\n", buffrecv[5]);
					reset_token(buffsend);
				
				/* The data is not addressed to this machine, pass it on. */
				} else {
					
					/* Copy the data to the send buffer. */
					strcpy(buffsend, buffrecv);
				}
				
			/* Received just the token. */
			} else if(buffrecv[2] == DLE && buffrecv[3] == ETX) {
			
				/* This machine has data to send. */
				if(is_ready) {
				
					/* Copy the frame to the send buffer. */
					strcpy(buffsend, frame);
					is_ready = 0;
				
				/* This machine does not have data to send. */
				} else {
					
					/* Pass on the token. */
					strcpy(buffsend, buffrecv);
				}
			}
			
			/* Write the send buffer. */
			if(write(client_fd, buffsend, sizeof(buffsend)) < 0) ReportError("write error\n");
	  	}
	}
	
	close(server_fd);
	close(client_fd);
}
