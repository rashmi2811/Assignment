#include "unp.h"

int main(void){
	int n_client = 0;
	int serverSock, clientSock;
	serverSock = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress;
	char buff[MAXLINE];
	time_t ticks;

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
	serverAddress.sin_port = htons(9999);
	Bind( serverSock, (SA *)&serverAddress, sizeof(serverAddress));
	Listen(serverSock, LISTENQ);

	int i=1,f=1;
	unsigned int j=1;
	while(i){ 

		if(j){
			clientSock = Accept(serverSock, (SA *) NULL, NULL);
			n_client++;
			time(&ticks);
			printf("Client %d connected to the Server on: %.24s\r\n\n", n_client,ctime(&ticks));

			while(1){
				bzero(buff, sizeof(buff));
				Read( clientSock, buff, MAXLINE);
				printf("Client %d: %s",n_client, buff);
				if(!strncmp("bye", buff, 3)){
					f=1;
					break;
				}

				bzero( buff, sizeof(buff));
				printf("Server: ");
				fgets( buff, sizeof(buff), stdin);
				Write( clientSock, buff, strlen(buff));

				if(!strncmp("bye", buff, 3)){
					f=0;
					break;
				}
			}

			close(clientSock);
			if(f)
				printf("\n[+]Client Disconnected from the server.");
			else
				printf("\n[+]Client was Removed from the server.");
		}
		else {
			break;
		}
		printf("\n\nEnter 0 to Exit and any other key to continue: ");
		scanf("%d",&j); 
		printf("\n");	
	}

	close(serverSock);
	printf("...Terminating the session wait 30 secs before running the server again...\n");
	return 0;
}
