#include "header.h"

int main(){
	
	int client_fd = Client();
	int server_fd = Server();
	
	if(client_fd < 0) {
		client_fd = Client();
	}
}
