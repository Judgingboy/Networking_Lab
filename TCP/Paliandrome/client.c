#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
int main()
{
    int clientsocket, port, isPalindromeResult;
    struct sockaddr_in serveraddr;
    socklen_t len;
    char message[100];

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    len = sizeof(serveraddr);
    serveraddr.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);

    printf("Enter the string to check if it's a palindrome: ");
    scanf("%s", message);
    printf("\nTrying to connect to the server...\n");
    connect(clientsocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Connected to the server.\n");
    printf("\nSending string to the server for palindrome check: %s\n",
           message);
    send(clientsocket, message, sizeof(message), 0);

    printf("\nReceiving result from server...\n");
    recv(clientsocket, &isPalindromeResult, sizeof(int), 0);
    if (isPalindromeResult)
        printf("%s is a palindrome.\n", message);
    else
        printf("%s is not a palindrome.\n", message);

    close(clientsocket);
    return 0;
}