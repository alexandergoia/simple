#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define NETCOPY 30000

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("usage : %s ip file\n", argv[0]);
		printf("the file must be in the same directory of working directory\n");
		exit(-1);
	}

	char buffer[16384];
	int count;
	int sockfd;
	struct sockaddr_in server;
	FILE *f;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&server, sizeof(server));
	
	server.sin_family = AF_INET;
	server.sin_port = htons(NETCOPY);
	
	inet_pton(AF_INET, argv[1], &server.sin_addr);
	if( connect(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("error\n");
		exit(-1);
	}

	write(sockfd, argv[2], strlen(argv[2]));
	
	f = fopen(argv[2], "r");
	int file_no = fileno(f);

	sleep(1);

	while((count = read(file_no, buffer, sizeof(buffer))) > 0) {
		write(sockfd, buffer, count);
		bzero(buffer, sizeof(buffer));
	}

	fflush(f);
	fclose(f);

	return 0;

}
