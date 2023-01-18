#include "unp.h"

int main( int argc, char **argv){
    if(argc != 2){
        printf("[-]Usage: %s <IP Address>\n",argv[0]);
        exit(0);
    }
    printf("IP Address: %s\n",argv[1]);
    int sockfd;
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    //char buff[MAXLINE+1];

    struct sockaddr_in serverAddress;
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9999);

    if(inet_pton(AF_INET, argv[1], &serverAddress.sin_addr)<=0){
        printf("[-]inet_pton() Error for %s\n", argv[1]);
        exit(1);
    }
    Connect(sockfd, (SA *)&serverAddress, sizeof(serverAddress));
    str_cli(stdin, sockfd);
    exit(0);
    return 0;
}
