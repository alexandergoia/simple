#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

#define NETCOPY 30000

void netcopy(int connfd);

int main(void)
{
	int listenfd, connfd;
	struct sockaddr_in server;
	int pid;

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(NETCOPY);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bind(listenfd, (struct sockaddr *) &server, sizeof(server));
	listen(listenfd, 64);

	while(1) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);
		pid = fork();
		if(pid != 0) {
			netcopy(connfd);
		}
	}
	return 0;
}

void netcopy(int connfd)
{
	char buffer[256];
	char name[256];
	char binbuff[16384];
	FILE * f;
	int n, size;

	bzero(buffer, sizeof(buffer));
	n = read(connfd, buffer, sizeof(buffer));

	bzero(name, sizeof(name));
	strcpy(name, buffer);
	name[n+1] = '\0';
	
	f = fopen(name, "w");
	int file_no = fileno(f);
	
	while((n = read(connfd, binbuff, sizeof(binbuff))) > 0) {
		write(file_no, binbuff, n);
		bzero(binbuff, sizeof(binbuff));
	}
	fflush(f);
	fclose(f);
	exit(0);
}
