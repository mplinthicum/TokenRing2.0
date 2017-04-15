#include "header.h"

int main(){
	
	int client_fd = Client("192.168.254.15");
	int server_fd = Server("192.168.254.14");
	
	if(client_fd < 0) {
		client_fd = Client("192.168.254.15");
	}
	
}
