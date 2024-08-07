/*******************************************************************
* Author: Henry Xiong
* Date: August 6, 2024

* Description: 
* This C program is used to communicate with the client by supplying them with a key to their message.
* It then decrypts their message through the Caesar Cipher logic

Usage:
* The maximum amount of clients is 5, use the compiler and type in the command ./server to use this program
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <ctype.h>

#define PORT 8080
#define BUFFER_SIZE 1024

/*******************************************************************
* Description: this function decrypts the message received from the client
                that's been shifted by a randomly generated key 
*******************************************************************/
void decrypt(char message[BUFFER_SIZE], int key) {
    for (unsigned long i = 0; i < strlen(message); i++) {
        if ((message[i] >= 'a' && message[i] <= 'z')) {
            message[i] = ((message[i] - 'a') - key) % 26 + 'a';
        } else if ((message[i] >= 'A' && message[i] <= 'Z')) {
            message[i] = ((message[i] - 'A') - key) % 26 + 'A';
        }
    }
}

/*******************************************************************
* Description: hosts a server that allows communication with the client that allows
                them to enter a message that gets encoded and then decoded into the
                the server.  The encryption has a randomly generated key from 1 to
                25 that shifts the ASCII value of each character in the message
*******************************************************************/
int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int client_count = 0;

    // Create A TCP socket for IPV4 domain
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return 1;
    }

    // Initialize address structure
    address.sin_family = AF_INET;    // IPV4 address
    address.sin_addr.s_addr = INADDR_ANY;  // INADDR_ANY allows connections from any IP address
    address.sin_port = htons(PORT);  // set PORT number appropritate for the network

     // Bind the socket to the specified address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    // Listen for connections. 
    if (listen(server_fd, 1) < 0) {  
        perror("listen");
        return 1;
    }

    // Keep accepting incoming connections and process requests
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            return 1;
        }

        // update client count 
        client_count++;
        printf("Connecting to Client %d\n", client_count);
        if (client_count > 5) {
            perror("Exceeded maximum client capacity\n");
            close(new_socket);
            return 1;
        }
        
        pid_t pid = fork();
        if (pid == 0) {  // child process
            close(server_fd);

            // what was sent from the client? "Hello from client, can you send me the key"
            char greeting_from_client[BUFFER_SIZE] = {0};
            read(new_socket, greeting_from_client, BUFFER_SIZE);
            printf("%s", greeting_from_client);

            // generate a random key 
            srand(time(NULL));
            int key = rand() % (25 - 1 + 1) + 1;

            // convert the key from integer to string with sprintf and send it to client
            char key_to_client[BUFFER_SIZE] = {0};
            sprintf(key_to_client, "%d", key);
            write(new_socket, key_to_client, strlen(key_to_client));

            while (1) {
                // reads the message that's going to be converted
                char msg_from_client[BUFFER_SIZE] = {0};
                read(new_socket, msg_from_client, BUFFER_SIZE);

                // once the user inputs quit into the terminal, terminate the loop
                if (strcmp(msg_from_client, "quit") == 0 || strcmp(msg_from_client, "QUIT") == 0) {
                    printf("Client %d terminated\n", client_count);
                    break;
                }
                
                decrypt(msg_from_client, key);

                write(new_socket, msg_from_client, strlen(msg_from_client));
            }

            close(new_socket);
            exit(1);
        }
        else {  // parent process
            close(new_socket);
        }
    }

    close(server_fd);
    return 0;
}