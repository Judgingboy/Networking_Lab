#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 256

int main()
{
    int clientsocket,port;
    char message[BUFFER_SIZE];

    socklen_t len;
    struct sockaddr_in serveraddr;

    clientsocket=socket(AF_INET,SOCK_STREAM,0);
    len=sizeof(serveraddr);
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    printf("\nEnter the port number:");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    printf("\nTrying to connect..\n");
    connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("\nConnection Established!\n");

    while(1)
    {
        printf("\nclient:");
        fgets(message,BUFFER_SIZE,stdin);
        write(clientsocket,message,BUFFER_SIZE);

        bzero(message,BUFFER_SIZE);
        read(clientsocket,message,BUFFER_SIZE);
        printf("\nServer:%s",message);
    }
    close(clientsocket);
    return 0;
}

