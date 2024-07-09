#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define BUFFER_SIZE 256
int main()
{
    char BUFFER[BUFFER_SIZE];
    char filename[20];
    int serversocket,newsocket,port;
    struct sockaddr_in serveraddr, clientaddr;
    //created a socket
    serversocket=socket(AF_INET,SOCK_STREAM,0);

    serveraddr.sin_family=AF_INET;
    printf("\nEnter the port:");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    //checking if the binding is happening or not
    if(bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr))==-1)
    {
        perror("Binding Failed!");        
    }
    if(listen(serversocket,5)==-1)
    {
        perror("Listen");
    }
    socklen_t len;
    len=sizeof(serveraddr);

    printf("\nWaiting For the connection..");
    newsocket=accept(serversocket,(struct sockaddr*)&serveraddr,&len);
    printf("\nConnection Established!");
    //Entering and sending the file

    printf("\nEnter the filename:");
    scanf("%s",filename);
    send(serversocket,filename,sizeof(filename),0);

    while(1)
    {
        int recvcheck=recv(newsocket,filename,sizeof(BUFFER),0);
        if(recvcheck ==-1)
        {
            perror("recv");

        }
        //if the check is passed the client connection is closed
        if(recvcheck==0)
        {
            break;
        }
        printf("\n%s\n",BUFFER);        
    }
    close(serversocket);
    close(newsocket);
}




    












