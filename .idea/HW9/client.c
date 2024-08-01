#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024


int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create TCP socket for IPV4 domain
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;  // AF_INET represents IPV4 address
    serv_addr.sin_port = htons(PORT);  // converts port number to network byte order

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use "127.0.0.1" for localhost or "localhost"

    // Connect to server with specified address and port number
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // read the action from stdin
    char action[BUFFER_SIZE] = {0};
    printf("Enter action: ");
    fgets(action, BUFFER_SIZE, stdin);


    return 0;
}
