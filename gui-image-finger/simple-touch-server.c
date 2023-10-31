/* Simple Touch, server program, written in C/Unix */
/* runs on Unix/Internet server machine		   */
/* client runs on Java (Windows, Linux) desktop	   */

#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>
#include <strings.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

void cpy_net(int from, int fd, long long count);
void sigchld();

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage : %s file-to-serve\n", argv[0]);
		return EXIT_FAILURE;
	}

	// angel();
	daemon(1, 1);
	signal(SIGCHLD, sigchld);

	FILE *file = fopen(argv[1], "r");
	struct sockaddr_in server;
	struct sockaddr_in client;

	int serv_sock;
	int cli_sock;
	int sin_size;

	pid_t proc;

	struct stat filestat;

	int from = fileno(file);
	fstat(from, &filestat);
	long long size = filestat.st_size;

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(9700);
	server.sin_addr.s_addr= INADDR_ANY;

	bzero(&server.sin_zero, sizeof(server.sin_zero));
	
	bind(serv_sock, (struct sockaddr *) &server, (socklen_t) sizeof(server));

	sin_size = sizeof(struct sockaddr_in);

	if(serv_sock < 0)
		return EXIT_FAILURE;

	listen(serv_sock, 8);

	for(;;) {
		cli_sock = accept (serv_sock, (struct sockaddr *) &client, (socklen_t *) &sin_size);
		
		proc = fork();

		switch(proc) {
			case 0:	cpy_net(from, cli_sock, size);
				close(cli_sock);
				return 0;

			default: close(cli_sock);
		}
	}

	return EXIT_SUCCESS;
}


void cpy_net(int from, int fd, long long count)
{
	sendfile(fd, from, NULL, count);
	lseek(from, 0L, SEEK_SET);
}

void sigchld()
{
	while(wait(NULL) > 0);
}
