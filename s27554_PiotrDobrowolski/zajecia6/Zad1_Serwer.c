#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 1985
#define BUFFER_SIZE 1024

int server_fd;
struct sockaddr_in server_addr;
struct sockaddr_in client_addr;
socklen_t addr_len;
int64_t error_size;
int64_t file_size;
FILE *file;
char buffer[BUFFER_SIZE];
int bytes_read;

void sigint_handler(int signal) {
    printf("Zamykanie serwera...\n");
    close(server_fd);
    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);
    addr_len = sizeof(client_addr);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(server_fd, 10) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Serwer nasłuchuje na porcie %d\n", PORT);

    while (1) {
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

        if (client_fd == -1) {
            perror("accept");
            continue;
        }

        printf("Połączenie od %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        if ((bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0) {
            int filename_len = atoi(buffer);
            recv(client_fd, buffer, filename_len, 0);
            buffer[filename_len] = '\0';

            printf("Żądanie pliku: %s\n", buffer);
            file = fopen(buffer, "rb");

            if (file == NULL) {
                perror("fopen");
                error_size = -1;
                send(client_fd, &error_size, sizeof(int64_t), 0);
            } else {
                fseek(file, 0, SEEK_END);
                file_size = ftell(file);
                fseek(file, 0, SEEK_SET);

                send(client_fd, &file_size, sizeof(int64_t), 0);

                while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                    send(client_fd, buffer, bytes_read, 0);
                }

                fclose(file);
            }
        }

        close(client_fd);
    }

    return 0;
}
