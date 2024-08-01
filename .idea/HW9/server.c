#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void toUpperCase(char *str) {
    int i = 0;
    while ((str[i] != '\0') && (str[i] != '\n')) {
        str[i] = toupper(str[i]);
        i++;
    }
}

void toLowerCase(char *str) {
    int i = 0;
    while ((str[i] != '\0') && (str[i] != '\n')) {
        str[i] = tolower(str[i]);
        i++;
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

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



        // TODO: Send response to client
        write(new_socket, sending, strlen(sending));

        // TODO: Close the socket
        close(new_socket);
    }

    return 0;
}


