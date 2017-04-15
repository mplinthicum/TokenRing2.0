#include "header.h"

/**
 * This routine establishes an active open connection.  That is, it creates 
 * a socket, and connects using it to a remote machine. The routine returns 
 * a file descriptor to be used to communicate with the remote machine.  
 * Make sure that you change the machine name from "vulcan" to that of 
 * the remote machine.  Also, change the port number to a suitable port 
 * number as indicated in the project writeup.
 */
int Client(char* client_ip) {

	struct sockaddr_in otheraddr;

	int s, n, code;
	
	/* Create the socket. */
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) ReportError("CLIENT ERROR: socket creation");
	
	/* Set the socket address. */
	bzero(&otheraddr, sizeof(otheraddr));
	otheraddr.sin_family = AF_INET;
	otheraddr.sin_port = PORT_NO;
	otheraddr.sin_addr.s_addr = inet_addr(client_ip);
	
	/* Connect to the server at otherhostname. */
	n = connect(s, (struct sockaddr*)&otheraddr, sizeof(otheraddr));
	
	if(n < 0) 
		return(n);
	else
		return(s);
}
