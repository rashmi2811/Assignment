#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>
#include	<errno.h>

#define MAXLINE 4096
#define SA struct sockaddr
#define LISTENQ 1024

int Socket(int family, int type, int protocol) {
    int n;
    if((n = socket(family,type,protocol)) < 0) {
        perror("[-]socket() Error");
        exit(1);
    }
    printf("[+]Socket Created\n");
    return n;
}

int Connect(int sockfd, SA *addr, socklen_t addrlen) {
    int n;
    if((n = connect(sockfd, addr, addrlen)) < 0) {
        perror("[-]connect() Error");
        exit(1);
    }
    printf("[+]Connection established\n");
    return n;
}

int Bind(int sockfd, SA *addr, socklen_t addrlen) {
    int n;
    if((n = bind(sockfd, addr, addrlen)) < 0) {
        perror("[-]bind() Error");
        exit(1);
    }
    printf("[+]Bind Successful\n");
    return n;
}

int Listen(int sockfd, int listenq) {
    int n;
    if((n = listen(sockfd, listenq)) < 0) {
        perror("[-]listen() Error");
        exit(1);
    }
    printf("[+]Listening for the client...\n");
    return n;
}

int Accept(int sockfd, SA *addr, socklen_t *addrlen) {
    int n;
    if((n = accept(sockfd, addr, addrlen)) < 0) {
        perror("[-]accept() Error");
        exit(1);
    }
    printf("[+]Client Connected\n");
    return n;
}

ssize_t Write(int sockfd, void *buff, size_t count) {
    ssize_t n;
    if((n = write(sockfd, buff, count)) < 0) {
        perror("[-]write() Error");
        exit(1);
    }
    printf("[+]Write implemented\n");
    return n;
}

ssize_t Read(int sockfd, void *buff, size_t count) {
    ssize_t n;
    if((n = read(sockfd, buff, count)) < 0) {
        perror("[-]read() Error");
        exit(1);
    }
    if(n != 0)
        printf("[+]Read Successful\n");
    return n;
}

void str_echo(int sockfd, int n_client) {
    char buff[MAXLINE];
    while(1) {
        bzero(buff, sizeof(buff));
        Read(sockfd, buff, MAXLINE);
        if(!strncmp("exit", buff, 4)){
            break;
        }
        printf("Client %d: %s", n_client, buff);
        Write(sockfd, buff, strlen(buff));
    }
    close(sockfd);
    printf("\n[+]Client %d Disconnected from the server.\n", n_client);
}

void str_cli(FILE *fp, int sockfd) {
    char buff[MAXLINE+1];
    while(1) {
        bzero(buff, sizeof(buff));
        printf("Client: ");
        fgets(buff, sizeof(buff), fp);
        Write(sockfd, buff, strlen(buff));
        if(!strncmp("exit", buff, 4))
            break;
        bzero(buff, sizeof(buff));
        Read(sockfd, buff, MAXLINE);
        printf("Server: %s", buff);
    }
    close(sockfd);
    printf("\n[+]Disconnected from the server.\n");
}
     
