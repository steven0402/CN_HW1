#include<stdio.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
	int sockfd, clientsockfd;
	//sockfd = socket(AF_INET, SOCK_STREAM,  0);
	char *msg = "ok";
	char receivemsg[100];
	struct addrinfo *res;
	struct addrinfo hint;
	struct sockaddr_in their_addr;
	socklen_t addr_size;
	char s[INET6_ADDRSTRLEN];
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;
	
	
	getaddrinfo(NULL, argv[1], &hint, &res);
	sockfd = socket(res->ai_family, res->ai_socktype,  res->ai_protocol);
	
	bind(sockfd, res->ai_addr, res->ai_addrlen);

	listen(sockfd, 10);
	addr_size = sizeof their_addr;
	
	while(1){
//printf("aaa\n");		
	clientsockfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);	
//printf("bbb\n");
		if (fork() == 0){
		while(recv(clientsockfd,receivemsg,sizeof(receivemsg),0) > 0)
		{
			//printf("yesah\n");	
		
			//printf("get!\n");
			inet_ntop(AF_INET, &(their_addr.sin_addr),s, sizeof(s));
			printf("receive from %s:%d\n",s,ntohs(their_addr.sin_port));
			send(clientsockfd, msg, strlen(msg), 0);
			//printf("yoyoyo\n");
		
		//printf("%s",receivemsg);
		//printf("aaa\n");
		}
		close(clientsockfd);
		}
		//close(clientsockfd);
		}
	
	//freeaddrinfo(res);
}
