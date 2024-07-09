#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<string.h>
#define BUFFER_SIZE 256

int main()
{
    int serversocket,clientsocket,port;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    char message[BUFFER_SIZE];
    //making a socket
    serversocket=socket(AF_INET,SOCK_STREAM,0);

    //initialising server address
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    printf("Enter the port:");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    //bind 
    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    len=sizeof(clientaddr);
    bzero((char*)&clientaddr,sizeof(clientaddr));

    //listen
    listen(serversocket,5);

    printf("\nWaiting for the client connection\n");
    clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&len);
    printf("\nClient connectivity received.\n");

    while(1)
    {
        //recieve messages
        bzero(message,BUFFER_SIZE);
        read(clientsocket,message,sizeof(message));
        printf("\nClient:%s",message);

        //send message to client
        printf("\nServer:");
        fgets(message,sizeof(message),stdin);
        write(clientsocket,message,strlen(message));

        if(strncmp(message, "exit", 4)==0)
        {
                break;
        }
    }
    close(serversocket);
    close(clientsocket);
    return 0;
}





