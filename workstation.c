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
	
	int num_fds;
	fd_set rset;	/* Declare an fd_set for read descriptors. */
	
	char buffsend[82], buffrecv[82];

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
		   
	  	if(num_fds == -1) {
		 	/* Code to handle errors. */
	  	}
	  	
		/* After this point, handle the ready descriptor(s). */
	  
	  	/* Check for ready data from the keyboard. */
	  	if(FD_ISSET(STDIN_FILENO, &rset)) {
	  	
	  		/* Get user input from the keyboard. */
			get_input(buffsend, sizeof(buffsend));
			
			/* Write to the receiver. */
			if(write(client_fd, buffsend, sizeof(buffsend)) < 0) ReportError("write error\n");
			
			/* Decrease the number of ready file descriptors. */
			num_fds--;
	  	}
	 
	  	/* Check for ready data from the communication channel. */
	  	if((num_fds > 0) && (FD_ISSET(server_fd, &rset))) {
	  	
			/* Read data from socket. */
			bzero(buffrecv, sizeof(buffrecv));
			if(read(server_fd, buffrecv, sizeof(buffrecv)) < 0) ReportError("read error\n");
			
			printf("Client says: %s\n", buffrecv);
			
			/* Write data to client. */
			bzero(buffsend, sizeof(buffsend));
			strcpy(buffsend, buffrecv);
			if(write(client_fd, buffsend, sizeof(buffsend)) < 0) ReportError("write error\n");
	  	}
	}
	
	close(server_fd);
	close(client_fd);
}
