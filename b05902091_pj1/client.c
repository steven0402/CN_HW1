#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main(int argc, char *argv[])
{
	clock_t mainstart = clock();
	char ips[argc][100];
	char ports[argc][100];
	char *msg = "test";
	char receivemsg[100];
	int t = 1000;
	int n = 0;
	int start = 1;
	
	if(strcmp(argv[1], "-t") == 0)
	{
		t = atoi(argv[2]);
		start = 3;
	}
	else if(strcmp(argv[1], "-n") == 0)
	{
		n = atoi(argv[2]);
		start = 3;
		
		if(argc >= 6){
		if(strcmp(argv[3], "-t") == 0)
		{
			t = atoi(argv[4]);
			start = 5;
		}
	}
	}
	//printf("t:%d, n:%d\n",t,n);
	//printf("argc:%d start:%d\n",argc,start);
	int count = 0;
	for(int i = start; i < argc; i++)
	{
		//printf("%s",argv[i]);
		
		int length = strlen(argv[i]);
		//printf("i=%d\n",length);
		int j = 0;
		int k = 0;
		//k = strcmp(argv[i][j],":");
		//printf("%c\n",argv[start][1]);
		char temp;
		temp = argv[i][j];
		
		while(temp != ':')
		{
			//printf("%c",argv[i][j]);

			ips[count][j] = temp;
			j++;
			temp = argv[i][j];
		}
		ips[count][j]='\0';
		j++;
		//printf("ip:%s\n",ips[i]);
		while(j < length)
		{
			ports[count][k] = argv[i][j];
			//printf("%c",ports[i][k]);
			k++;
			j++;

		}
		ports[count][k]='\0';
		//printf("port:%s\n",ports[0]);
		count ++;
		
	}
	//printf("port:%s\n",ports[0]);
	int no_of_port = argc - start;
	//printf("no_of_port:%d\n",no_of_port);
	int sockfd[no_of_port];
	//sockfd = socket(AF_INET, SOCK_STREAM,  0);
	struct addrinfo *res[no_of_port];
	struct addrinfo hints;
	//struct sockaddr_in sa;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	if(n != 0){
	for(int i = 0; i < no_of_port; i++)
	{
	
	getaddrinfo(ips[i], ports[i], &hints, &res[i]);
	sockfd[i] = socket(res[i]->ai_family, res[i]->ai_socktype,  res[i]->ai_protocol);
	connect(sockfd[i], res[i]->ai_addr, res[i]->ai_addrlen);

	for(int j = 0; j < n; j++)
	{

	//struct hostent *ghbn = gethostbyname(ips[i]);
	//struct in_addr* address;
	//address.s_addr = inet_addr(ips[i]);
	//address = (struct in_addr *) res[i]->ai_addr;
	struct sockaddr_in* saddr = (struct sockaddr_in*)res[i]->ai_addr;
	char *ip = inet_ntoa(saddr->sin_addr);

	send(sockfd[i], msg, strlen(msg), 0);
	clock_t before = clock();
	float ms = 0;
	int work = 1;
	while(work == 1)
	{
	ms = (float)(clock() - before)*1000/ CLOCKS_PER_SEC;
	if(ms < t){
	if(recv(sockfd[i],receivemsg,sizeof(receivemsg),0) > 0)
	{
		/*struct hostent *ghbn = gethostbyname(ips[i]);
		struct in_addr *address;
		address = (struct in_addr *) ghbn->h_addr_list;*/
		printf("recv from %s, RTT = %f msec\n",ip, ms);
		//memset(receivemsg, 0, sizeof(receivemsg));
		work = 0;
	
	}
	}else
	{
		/*struct hostent *ghbn = gethostbyname(ips[i]);
		struct in_addr *address;
		address = (struct in_addr *) ghbn->h_addr_list;*/
		printf("timeout when connect to %s\n", ip);
		work = 0;
	}
	}
	}
	close(sockfd[i]);
	}
}
else
{
	for(int i = 0; i < no_of_port; i++)
	{
	
	getaddrinfo(ips[i], ports[i], &hints, &res[i]);
	sockfd[i] = socket(res[i]->ai_family, res[i]->ai_socktype,  res[i]->ai_protocol);
}
	while(1){
	for(int i = 0; i < no_of_port; i++)
	{
	
	//getaddrinfo(ips[i], ports[i], &hints, &res[i]);
	//sockfd[i] = socket(res[i]->ai_family, res[i]->ai_socktype,  res[i]->ai_protocol);
	connect(sockfd[i], res[i]->ai_addr, res[i]->ai_addrlen);
	//struct hostent *ghbn = gethostbyname(ips[i]);
	//struct in_addr address;
	//address.s_addr = inet_addr(ips[i]);
	//address = (struct in_addr *) ghbn->h_addr_list;
	//char *ip = inet_ntoa(address);
	struct sockaddr_in* saddr = (struct sockaddr_in*)res[i]->ai_addr;
	char *ip = inet_ntoa(saddr->sin_addr);
	//printf("%d time\n",j);
	clock_t before = clock();
	send(sockfd[i], msg, strlen(msg), 0);
	float ms = 0;
	int work = 1;
	while(work == 1)
	{
	ms = (float)(clock() - before)*1000/ CLOCKS_PER_SEC;
	if(ms <= t){
	if(recv(sockfd[i],receivemsg,sizeof(receivemsg),0) > 0)
	{
		/*struct hostent *ghbn = gethostbyname(ips[i]);
		struct in_addr *address;
		address = (struct in_addr *) ghbn->h_addr_list;*/
		printf("recv from %s, RTT = %f msec\n",ip, ms);
		//memset(receivemsg, 0, sizeof(receivemsg));
		work = 0;
	
	}
	}else
	{
		/*struct hostent *ghbn = gethostbyname(ips[i]);
		struct in_addr *address;
		address = (struct in_addr *) ghbn->h_addr_list;*/
		printf("timeout when connect to %s\n", ip);
		work = 0;
	}
	//close(sockfd[i]);
	}
	}
		
}

}
/*	getaddrinfo(NULL, ports[0], &hints, &res[0]);
	sockfd[0] = socket(res[0]->ai_family, res[0]->ai_socktype,  res[0]->ai_protocol);
	connect(sockfd[0], res[0]->ai_addr, res[0]->ai_addrlen);
	send(sockfd[0], msg, strlen(msg), 0);
	if(recv(sockfd[0],receivemsg,sizeof(receivemsg),0) != 0)
		printf("%s\n",receivemsg);
	send(sockfd[0], msg, strlen(msg), 0);
	if(recv(sockfd[0],receivemsg,sizeof(receivemsg),0) != 0)
		printf("%s\n",receivemsg);*/
}
