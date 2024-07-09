#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
// Function to check if a string is palindrome
int isPalindrome(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++)
    {
        if (str[i] != str[length - i - 1])
            return 0; // Not a palindrome
    }
    return 1; // Palindrome
}
int main()
{
    int serversocket, clientsocket, port, isPalindromeResult;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char message[100];
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(serversocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    bzero((char *)&clientaddr, sizeof(clientaddr));
    len = sizeof(clientaddr);
    listen(serversocket, 5);
    printf("\nWaiting for client connection...\n");
    clientsocket = accept(serversocket, (struct sockaddr *)&clientaddr, &len);
    printf("Client connectivity received.\n");
    printf("\nReading string from the client...\n");
    recv(clientsocket, message, sizeof(message), 0);
    printf("String received from client: %s\n", message);
    isPalindromeResult = isPalindrome(message);
    printf("\nSending result to the client...\n");
    send(clientsocket, &isPalindromeResult, sizeof(int), 0);
    close(clientsocket);
    close(serversocket);
    return 0;
}
