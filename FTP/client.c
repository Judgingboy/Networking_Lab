#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define BUFFER_SIZE 256
FILE *fp;
int main()
{
    char BUFFER[BUFFER_SIZE];
    char filename[20];
    int serversocket,port;
    struct sockaddr_in serveraddr;
    //created a socket
    serversocket=socket(AF_INET,SOCK_STREAM,0);
    serveraddr.sin_family=AF_INET;
    printf("\nEnter the port:");
    scanf("%d",&port);
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    printf("\nTrying to connect");    
    connect(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("\nConnectiion Established!");

    recv(serversocket,filename,sizeof(filename),0);
    printf("%s",filename);
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        perror("Fopen");        
    }
    else
    {
        while(fgets(BUFFER,sizeof(BUFFER),fp)!=NULL)
        {
            send(serversocket,BUFFER,sizeof(BUFFER),0);            
        }
        fclose(fp);
    }
    close(serversocket);
}

    






