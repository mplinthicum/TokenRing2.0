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
	struct hostent *myname;

	int s, fd, otherlength = sizeof(otheraddr);
	char *hostname = "co2048-14.ece.iastate.edu", ch;

	/* Create the socket. */
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) ReportError("SERVER ERROR: socket creation");
	
	/* Set socket parameters. */
	myname = gethostbyname(hostname);
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family  = AF_INET;
	myaddr.sin_port = PORT_NO;
	myaddr.sin_addr.s_addr = inet_addr(server_ip);
	
	//bcopy(myname->h_addr_list[0], &myaddr.sin_addr, myname->h_length);
	
	printf("HOSTNAME: %s, %s\n", myname->h_name, myname->h_addr_list[0]);
	
	/* Bind the socket to the set address. */
	if(bind(s, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0) ReportError("SERVER ERROR: socket bind");

	/* Listen for and accept incoming connection. */
	listen(s, 1);
	if((fd = accept(s, (struct sockaddr*)&otheraddr, &otherlength)) < 0) ReportError("SERVER ERROR: socket accept");

	fprintf(stdout, "Connected\n");

	return(fd);
}
