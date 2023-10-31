#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

int main(int argc, char *argv[])
{
	if(argc != 2) {
		printf("usage : %s text_file_to_finger\n", argv[0]);
		return 0;
	}

	daemon(1, 1);

	struct sigaction x = {SIG_IGN};
	sigaction(SIGPIPE, &x, NULL);

	struct sockaddr_in servaddr;
	int listenfd, connfd;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port	 = htons(7900);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, 32);

	while(1) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, (socklen_t *) NULL);
		

		FILE *f = fopen(argv[1], "r");
		char line[128];
		bzero(line, sizeof(line));
		
		while(fgets(line, sizeof(line), f)) {
			int err;
			err = write(connfd, line, strlen(line));
		//	sleep(1);
			bzero(line, sizeof(line));
			if(err == -1) goto end;
		}

end:		fclose(f);
		close(connfd);
	}

	return 0;
}

