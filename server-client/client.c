//Georgoulas Vasilhs A.M.: 2954
//Vamvas Ioannis A.M.: 2943

/* client.c

*/


#include "utils.h"
#include <pthread.h>

#define SERVER_PORT     6767
#define BUF_SIZE        2048
#define MAXHOSTNAMELEN  1024
#define MAX_STATION_ID   4
#define ITER_COUNT         1
#define GET_MODE           1
#define PUT_MODE           2
#define USER_MODE          3
#define NTHREADS	  6

pthread_t tid[NTHREADS];

int st = 2020;
int st1 = 2020;
int count = 0;

void *thread_function(void *);

/**
 * @name print_usage - Prints usage information.
 * @return
 */
void print_usage() {
  fprintf(stderr, "Usage: client [OPTION]...\n\n");
  fprintf(stderr, "Available Options:\n");
  fprintf(stderr, "-h:             Print this help message.\n");
  fprintf(stderr, "-a <address>:   Specify the server address or hostname.\n");
  fprintf(stderr, "-o <operation>: Send a single operation to the server.\n");
  fprintf(stderr, "                <operation>:\n");
  fprintf(stderr, "                PUT:key:value\n");
  fprintf(stderr, "                GET:key\n");
  fprintf(stderr, "-i <count>:     Specify the number of iterations.\n");
  fprintf(stderr, "-g:             Repeatedly send GET operations.\n");
  fprintf(stderr, "-p:             Repeatedly send PUT operations.\n");
}

/**
 * @name talk - Sends a message to the server and prints the response.
 * @server_addr: The server address.
 * @buffer: A buffer that contains a message for the server.
 *
 * @return
 */
void talk(const struct sockaddr_in server_addr, char *buffer) {
  char rcv_buffer[BUF_SIZE];
  int socket_fd, numbytes;
      
  // create socket
  if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    ERROR("socket()");
  }

  // connect to the server.
  if (connect(socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
    ERROR("connect()");
  }
  
  // send message.
  write_str_to_socket(socket_fd, buffer, strlen(buffer));
      
  // receive results.
  printf("Result: ");
  do {
    memset(rcv_buffer, 0, BUF_SIZE);
    numbytes = read_str_from_socket(socket_fd, rcv_buffer, BUF_SIZE);
    if (numbytes != 0)
      printf("%s", rcv_buffer); // print to stdout
  } while (numbytes > 0);
  printf("\n");
      
  // close the connection to the server.
  close(socket_fd);
}

/**
 * @name main - The main routine.
 */
int main(int argc, char **argv) {
  int i,j;
  
  for(i=0; i < NTHREADS; i++){
	if(i%2==0){
		count = 0;
	}else{
		count = 1;
	}
	int *c = malloc(sizeof(*c));
	*c = count;
  	pthread_create( &tid[i], NULL, thread_function, c );
	//free(c);
  }
  for(j=0;j<NTHREADS;j++){
 	pthread_join(tid[j],NULL);
  }

  return 0;
}

void *thread_function(void *dummyPtr){
	char *host = NULL;
	char snd_buffer[BUF_SIZE];
	int value,station;
	struct sockaddr_in server_addr;
	struct hostent *host_info;
	host = "localhost";
	if ((host_info = gethostbyname(host)) == NULL) { 
		ERROR("gethostbyname()"); 
	}
	int cnt = *(int *)dummyPtr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr = *((struct in_addr*)host_info->h_addr);
	server_addr.sin_port = htons(SERVER_PORT);
	
	for (station = 0; station < MAX_STATION_ID; station++) {
		memset(snd_buffer, 0, BUF_SIZE);
		if (cnt == 0) {
        		// Repeatedly GET.
			sprintf(snd_buffer, "GET:station.%d", st1);
			cnt=1;
		} else if (cnt == 1) {
        		// Repeatedly PUT.
        		// create a random value.
			value = rand() % 65 + (-20);
			sprintf(snd_buffer, "PUT:station.%d:%d", st, value);
			cnt = 0;
		}
		printf("Operation: %s\n", snd_buffer);
		talk(server_addr, snd_buffer);
	}
	return 0;
}
