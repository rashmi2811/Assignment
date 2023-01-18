#include "unp.h"

int main(void){
    int n_client = 0;
    int serverSock, clientSock;
    serverSock = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    time_t ticks;
    pid_t childpid;

    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
    serverAddress.sin_port = htons(9999);
    Bind( serverSock, (SA *)&serverAddress, sizeof(serverAddress));
    Listen(serverSock, LISTENQ);

    while(1){ 

            clientSock = Accept(serverSock, (SA *) NULL, NULL);
            n_client++;
            time(&ticks);
            printf("Client %d connected to the Server on: %.24s\r\n\n", n_client,ctime(&ticks));

            if((childpid = fork()) == 0) {
                close(serverSock);
                str_echo(clientSock, n_client);
                exit(0);
            }
            close(clientSock);
    }
    return 0;
}
