#include "header.h"

/**
 * This routine establishes a passive open connection.  That is, it creates 
 * a socket, and passively wait for a connection.  Once a connection request 
 * has been received, it echoes "connected" on the screen, and return 
 * a file descriptor to be used to communicate with the remote machine.  
 * Make sure that you change the machine name from "vulcan" to that you 
 * will be running your process on. Also, change the port number to 
 * a suitable port number as indicated in the project writeup.
 */
int Server(char* server_ip) {

	struct sockaddr_in myaddr, otheraddr;

	int s, fd, otherlength = sizeof(otheraddr);

	/* Create the socket. */
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) ReportError("SERVER ERROR: socket creation");
	
	/* Set socket parameters. */
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family  = AF_INET;
	myaddr.sin_port = PORT_NO;
	myaddr.sin_addr.s_addr = inet_addr(server_ip);
	
	/* Bind the socket to the set address. */
	if(bind(s, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0) ReportError("SERVER ERROR: socket bind");

	/* Listen for and accept incoming connection. */
	listen(s, 1);
	if((fd = accept(s, (struct sockaddr*)&otheraddr, &otherlength)) < 0) ReportError("SERVER ERROR: socket accept");

	fprintf(stdout, "Connected\n");

	return(fd);
}
