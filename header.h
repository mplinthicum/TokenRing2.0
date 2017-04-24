#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

#define ReportError(msg)	{perror(msg); exit(-1);}
#define PORT_NO				2840
#define DLE					0x10
#define SYN					0x16
#define ETX					0x03
#define STX					0x02

/* Hostname: co2048-XX.ece.iastate.edu */
/* Coover 2048 IPs: 192.168.254.XX */

int Server(char* server_ip);
int Client(char* client_ip);
int get_data(char* buffer, int length);
void reset_token(char* buff);
void fill_frame(char* frame, char machine_id, char* data);

/* I don't know why these are here yet. */
//long random(), M= 2147483647;
void srandom(unsigned);
void IntroduceError(char*, double);
char *GenerateData(int);
double floor(double);
char linebuffer[100];


