#include <sys/time.h>

/**
 * The following code will put the standard input and the socket descriptor
 * in the select function to be inspected for reading.  When the select
 * function returns, the descriptors are inspected to find out which one
 * is ready.   This code can be modified to handle files and sockets which
 * become ready for writing.
 */

	/* Assume sd is the data channel socket & STDIN_FILENO is the standard input file descriptor (it is 0). */
	int n;
	
	/* Declare an fd_set for read descriptors. */
	fd_set rset;
	
	...

	/* Endless loop, if you want continuous operation. */
	while(1) {
	
		/* Clear all bits in rset, set the standard input bit, and set the socket descriptor bit. */
		FD_ZERO(&rset);
		FD_SET(STDIN_FILENO, &rset);
		FD_SET(sd, &rset);
 		n = select((sd > STDIN_FILENO ? sd : STDIN_FILENO) + 1, &rset, NULL, NULL, NULL);
 		
		/* Select blocks, and n is the number of ready descriptors. */
		if((n == -1) && (errno == EINTR)) /* interruption */
		   continue;
		   
	  	if((n== -1) {
		 	/* Code to handle errors. */
	  	}
	  	
		/* After this point, handle the ready descriptor(s). */
	  
	  	/* Check for ready data from the keyboard. */
	  	if(FD_ISSET(STDIN_FILENO, &rset)) {
	  	
			... 
			
			/* Read data from the standard input. */
			
			n--;
	  	}
	 
	  	/* Check for ready data from the communication channel. */
	  	if((n > 0 ) && (FD_ISSET(sd, &rset))) {
	  	
			/* Socket is ready for reading. */
			
			... 
			
			/* Read data from socket. */
	  	}
	}
	 	


