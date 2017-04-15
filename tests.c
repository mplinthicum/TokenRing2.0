#include "header.h"

int main(int argc, char **argv){

	/* Check if IPs were provided. */
    if (argc != 3) {
        printf("Usage: %s <server IP> <client IP>\n", argv[0]);
        return -1;
    }
	
	/* Client IP is next computer. */
	int client_fd = Client(argv[2]);
	int server_fd = Server(argv[1]);
	
	if(client_fd < 0) {
		client_fd = Client(argv[2]);
	}
	
	close(server_fd);
	close(client_fd);
}
