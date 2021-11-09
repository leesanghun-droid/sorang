#include "../include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


int socket_listenFD_init()
{
    int listenFD;
    int portno=52205;
    struct sockaddr_in serv_addr;

    printf("try_soket_open... \n");
    listenFD = socket(AF_INET, SOCK_STREAM, 0);

    if (listenFD < 0)
    {
        printf("[soket_open_faild]\n");
        return -1;
    }
    else
        printf("[soket_open_success]\n");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(52205);

    printf("try_binding... [ %d ] \n",portno);

    int result=0;

    result = bind(listenFD, (struct sockaddr *) &serv_addr,sizeof(serv_addr));

        if (result < 0) 
        {
            printf("[bind_faild]\n");
            return -1;
        }
        else
        {
            printf("[bind_success]\n");
        }   

    printf("try_listen... \n");
    int R_listen = listen(listenFD,5);
    if (R_listen < 0) 
    {
        printf("[listen_faild]\n");
        return -1;
    }
    else
        printf("[listen_success]\n");

    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(listenFD, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    return listenFD;
}

extern char* input_host_address;
extern int port_num;

int client_connect()
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        printf("ERROR opening socket\n");
        return -1;
    }
    server = gethostbyname(input_host_address);
    if (server == NULL) {
        printf("ERROR, no such host\n");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port_num);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("ERROR connecting");
        return -1;
    }

    return sockfd;
}

int add_client(int fd)
{
    socklen_t clilen;
    struct sockaddr_in cli_addr;

    clilen = sizeof(cli_addr);

    int new_clientFD = accept(fd, (struct sockaddr *) &cli_addr, &clilen);
    return new_clientFD;
}

/*
int newsockfd; 
socklen_t clilen;
char buffer[256];
struct sockaddr_in cli_addr;

void wait_client()
{
    clilen = sizeof(cli_addr);
    bzero(buffer,256);
    int client_status = recv(newsockfd,buffer,sizeof(buffer),0);
    if(client_status>0)
    {
        printf("%s\n",buffer);
    }else{
         printf("wait Client...\n");
         newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) 
            printf("[faild]\n");
        else
            {
            printf("[client_connected]\n");
        }
    }
}
*/
int tcpip_free()
{
    //printf("close_sockfd\n");
    //close(sockfd);
    //printf("close_newsockfd\n");
    //close(newsockfd);
}


    //bzero(buffer,256);
    //int client_status = recv(newsockfd,buffer,sizeof(buffer),0);