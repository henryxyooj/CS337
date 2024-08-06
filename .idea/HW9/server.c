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

void decrypt(char message[BUFFER_SIZE], int key) {
    for (unsigned long i = 0; i < strlen(message); i++) {
        if ((message[i] >= 'a' && message[i] <= 'z')) {
            message[i] = ((message[i] - 'a') - key) % 26 + 'a';
        } else if ((input[i] >= 'A' && input[i] <= 'Z')) {
            message[i] = ((message[i] - 'A') - key) % 26 + 'A';
        }
    }
}

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

        if (fork() == 0) {  // child process
            // what was sent from the client?
            char msg_from_client[BUFFER_SIZE] = {0};
            read(new_socket, msg_from_client, BUFFER_SIZE);
            printf("%s", msg_from_client);

            // generate a random key
            srand(time(NULL));
            int key = rand() % (25 - 1 + 1) + 1;
            printf("Key from server: %d", key);

            // convert the key from integer to string with sprintf and send it to client
            char key_to_client[BUFFER_SIZE] = {0};
            sprintf(key_to_client, "%d", key);
            write(new_socket, key_to_client, strlen(key_to_client));

            while (1) {
                // reads the message that's going to be converted
                read(new_socket, key_to_client, BUFFER_SIZE);

                if (strcmp(key_to_client, "quit") == 0 || strcmp(key_to_client, "QUIT") == 0) {
                    printf("Client %d terminated\n", client_count);
                    break;
                }

                char encoded_msg[BUFFER_SIZE] = {0};
                decrypt(encoded_msg, key);
                printf("Encoded message: %s");

                write(new_socket, key_to_client, strlen(key_to_client));
            }

            close(new_socket);
        }
        else {  // parent process
            close(new_socket);
        }
    }

    return 0;
}


