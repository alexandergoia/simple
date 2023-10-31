/* Simple finger server, programmed by Alexandru Goia       */
/* alexander@unixcoder.net  ;  http://unixcoder.net/        */
/* Compile & run : gcc 3inger.c -o 3inger ; ./3inger &	    */
/* Call server : finger string_containing_{1,2,3}@my_server */
/* Or better : telnet my_server finger_port                 */

/* MMVIII.I - MMXIV.II - MMXXIII.X  = all versions          */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define FINGER	79

int main()
{

int i;

char buffer[1024];
char *inger;

char *msg1= "First of the three angels !\n";
char *msg2= "The second of the three angels !\n";
char *msg3= "The third of the three angels !\n";

char *mesaj1 = "Welcome to the simple I/O (0xf inger) server of the 3 angels !\n";

int len1, len2, len3;
int lung1;

struct sockaddr_in * server = malloc(sizeof(struct sockaddr_in));
struct sockaddr_in * client = malloc(sizeof(struct sockaddr_in));

int sockfd, new_fd;
int sin_size;

len1 = strlen(msg1);
len2 = strlen(msg2);
len3 = strlen(msg3);

lung1 = strlen(mesaj1);

sin_size= sizeof (*client);
sockfd=socket(AF_INET, SOCK_STREAM, 0);

server->sin_family=AF_INET;
server->sin_port=htons(FINGER);
server->sin_addr.s_addr=INADDR_ANY;

memset(server->sin_zero, '\0', sizeof(server->sin_zero));

if(!bind(sockfd, (struct sockaddr *) server, (socklen_t) sizeof(*server)))
	daemon(1,1);

while(1)
 {
 listen(sockfd, 500);
 for(i=0;i<sizeof(buffer);i++) buffer[i]='0';
 new_fd=accept(sockfd, (struct sockaddr *)client, (socklen_t *) &sin_size);

 write(new_fd, mesaj1, lung1);
 
 read(new_fd, buffer, sizeof(buffer));

 inger=strchr(buffer, '1');
 if(inger != NULL) 
	write(new_fd, msg1, len1);
 
 inger=strchr(buffer, '2');
 if(inger != NULL)
	write(new_fd, msg2, len2);
 
 inger=strchr(buffer, '3');
 if(inger != NULL)
	write(new_fd, msg3, len3);
  
 close(new_fd);
 }

return 0;
}
