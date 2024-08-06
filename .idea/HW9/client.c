#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void encrypt(char message[BUFFER_SIZE], int key) {
    for (unsigned long i = 0; i < strlen(message); i++) {
        if ((message[i] >= 'a' && message[i] <= 'z')) {
            message[i] = ((message[i] - 'a') + key) % 26 + 'a';
        } else if ((message[i] >= 'A' && message[i] <= 'Z')) {
            message[i] = ((message[i] - 'A') + key) % 26 + 'A';
        }
    }
}

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
    char greeting[BUFFER_SIZE] = "Hello from client, can you send me the key?\n";
    write(sock, greeting, strlen(greeting));

    // upon receiving the key from the server, the client prompts the user to input a message from stdin
    char server_message[BUFFER_SIZE] = {0};

    // get the key from the server
    read(sock, server_message, strlen(server_message));
    int key = atoi(server_message);
    printf("Key from server: %d", key);

    // until user inputs "quit", keep sending encrypted messages that's been shifted to the server
    while (1) {
        // take the input and store it into message to prepare the socket for the server
        char message[BUFFER_SIZE] = {0};
        printf("Enter a message: ");
        fgets(message, BUFFER_SIZE, stdin);

        // once the user inputs quit into the terminal, terminate the loop
        if (strcmp(message, "quit") == 0 || strcmp(message, "QUIT") == 0) {
            write(sock, "quit", strlen("quit"));
            break;
        }

        // encrypt it and send the message to the server
        encrypt(message, key);
        write(sock, message, strlen(message));

        // receive the decrypted message from the server
        read(sock, server_message, BUFFER_SIZE);
        printf("Encoded message (type 'quit' to exit): %s", server_message);

    }

    //if the user inputs "quit", the client sends the quit message and closes its socket, and terminates
    close(sock);

    return 0;
}
