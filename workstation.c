#include "header.h"

int main(int argc, char **argv){

	/* Check if correct parameters were provided. */
    if (argc != 4) {
        printf("Usage: %s <server IP> <client IP> <machine ID>\n", argv[0]);
        printf("\t       <server IP> : The IP address of the current machine.\n");
        printf("\t       <client IP> : The IP address of the subsequent machine.\n");
        printf("\t       <machine ID>: THe uniqe ID assigned to this machine.\n");
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
	
	/* Endless loop for continuous operation. */
	while(1) {
	
	}
	
	close(server_fd);
	close(client_fd);
}
