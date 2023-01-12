#include "unp.h"

int main( int argc, char **argv){
	if(argc != 2){
		printf("[-]Usage: %s <IP Address>\n",argv[0]);
		exit(0);
	}
	char *ip = argv[1];
	printf("IP Address: %s\n",ip);
	int sockfd,f=1;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	char buff[MAXLINE+1];

	struct sockaddr_in serverAddress;
	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9999);

	if(inet_pton(AF_INET, argv[1], &serverAddress.sin_addr)<=0){
		printf("[-]inet_pton() Error for %s\n", argv[1]);
		exit(1);
	}
	Connect(sockfd, (SA *)&serverAddress, sizeof(serverAddress));

	while(1) {
		bzero( buff, sizeof(buff));
		printf("Client: ");
		fgets( buff, sizeof(buff), stdin);
		Write( sockfd, buff, strlen(buff));
		if(!strncmp("bye", buff, 3)){
			f=1;
			break;
		}

		bzero( buff, sizeof(buff));
		Read( sockfd, buff, MAXLINE);
		printf("Server: %s", buff);
		if(!strncmp("bye", buff, 3)){
			f=0;
			break;
		}
	}

	close(sockfd);
	if(f){
		printf("\n[+]Disconnected from the server.\n");
	}
	else{
		printf("\n[+]Removed from the server.\n");
	}
	return 0;
}
