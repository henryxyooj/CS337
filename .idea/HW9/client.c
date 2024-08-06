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

    // send a greeting to the server and requests the encryption key in the same message
    char *greeting[BUFFER_SIZE] = "Hello from client!  Requesting an encryption key...\n";
    write(sock, greeting, strlen(greeting));

    // upon receiving the key from the server, the client prompts the user to input a message from stdin
    char message[BUFFER_SIZE] = {0};
    fgets(message, BUFFER_SIZE, stdin);
    printf("Enter a message: ");

    // until user inputs "quit", keep sending encrypted messages that's been shifted to the server
    while (strcmp(message, "quit") != 0 && strcmp(message, "QUIT") != 0) {
        write(sock, message, strlen(message));
    }

    //if the user inputs "quit", the client sends the quit message and closes its socket, and terminates
    close(sock);

    return 0;
}
