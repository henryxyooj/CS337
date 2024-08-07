/*******************************************************************
* Author: Henry Xiong
* Date: August 6, 2024

* Description:
* This C program is used by the client to send a message to the server to get a key that then shifts
* each char within that message by how ever much the randomly generated key gives to the client

Usage:
* Use the compiler and type in the command ./client, and then type into the terminal the message you'd like to
* encode

Citations:
* https://stackoverflow.com/questions/22726245/c-socket-client-sending-newline-character
* https://www.youtube.com/watch?v=AQPsGkRgVBE&ab_channel=PortfolioCourses
* I had a hard time understanding how to use this function, but turns out I just needed to see
* more examples on how to use it.  By having the second parameter being "\n", C is going through
* each char individually and checking to see if "\n" is there.  So what happens is, once C finds
* where that "\n" is at, it returns the number of char it had to iterate through to get to that "\n"
* line 73 is how I used it
* Also just realized that I could've done something similar to this with the read function, since it returns
* the number of char it reads through too.  char = read(sock, dest, BUFFER_SIZE) and then dest[char] = "\0"
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/*******************************************************************
* Description: this function encrypts the client's message that's been
                shifted by the amount generated by the server, known as
                the key
*******************************************************************/
void encrypt(char message[BUFFER_SIZE], int key) {
    for (unsigned long i = 0; i < strlen(message); i++) {
        if ((message[i] >= 'a' && message[i] <= 'z')) {
            message[i] = ((message[i] - 'a') + key) % 26 + 'a';
        } else if ((message[i] >= 'A' && message[i] <= 'Z')) {
            message[i] = ((message[i] - 'A') + key) % 26 + 'A';
        }
    }
}

/*******************************************************************
* Description: this function communicates with the server that allows
                their input to get through via an encryption decided by
                the server through the server's key
*******************************************************************/
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
    char key_server_message[BUFFER_SIZE] = {0};
    read(sock, key_server_message, BUFFER_SIZE);
    key_server_message[strcspn(key_server_message, "\n")] = '\0';
    int key = atoi(key_server_message);
    printf("Key from server: %d\n", key);

    // until user inputs "quit", keep sending encrypted messages that's been shifted to the server
    while (1) {
        // take the input and store it into message to prepare the socket for the server
        char message[BUFFER_SIZE] = {0};
        printf("Enter message (type 'quit' to exit): ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0';

        // once the user inputs quit into the terminal, terminate the loop
        if (strcmp(message, "quit") == 0 || strcmp(message, "QUIT") == 0) {
            write(sock, "quit", strlen("quit"));
            break;
        }

        // encrypt it and send the message to the server
        encrypt(message, key);
        write(sock, message, strlen(message));
        printf("Encoded message: %s\n", message);

        // receive the decrypted message from the server
        char decrypted_msg[BUFFER_SIZE] = {0};
        read(sock, decrypted_msg, BUFFER_SIZE);
        decrypted_msg[strcspn(decrypted_msg, "\n")] = '\0';
        printf("Response from server: %s\n", decrypted_msg);
    }

    //if the user inputs "quit", the client sends the quit message and closes its socket, and terminates
    close(sock);

    return 0;
}
