#include "stdio.h"

#include "strings.h"
#include "stdlib.h"

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "unistd.h"

const unsigned int PORT = 7;
const unsigned int BUFFER_LENGTH = 1024;

typedef struct sockaddr sock;

int main() {

    int pid = fork();
    if (pid > 0) {
        printf("PID = %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    struct sockaddr_in server, client;
    int fd_socket = socket(AF_INET, SOCK_DGRAM, 0);
    char buffer[BUFFER_LENGTH];

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int r = bind(fd_socket, (sock *) &server, sizeof(server));
    if (r < 0) {
        printf("R = %d\n", r);
        exit(EXIT_FAILURE);
    }
    while (1) {
        unsigned int client_length = sizeof(client);
        int n = recvfrom(fd_socket, buffer, BUFFER_LENGTH, 0, (sock*) &client, &client_length);

        printf("Server: %s", buffer);
        sendto(fd_socket, buffer, n, 0, (sock *)&client, client_length);
    }
    close(fd_socket);
    return 0;
}
