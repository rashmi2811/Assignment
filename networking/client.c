#include "unp.h"

int main (int argc, char **argv) {

	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if(argc != 2)
		printf("usage: client <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5000);

	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s", argv[1]);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	//int count = 0;
	while((n = Read(sockfd, recvline, MAXLINE)) > 0) {
		//count++;
		printf("\n%d ",n);
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF) {
			printf("fputs error");
			exit(1);
		}
	}
	//printf("%d\n",count);

	exit(0);
}
