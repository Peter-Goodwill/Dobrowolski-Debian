#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 1985
#define BUFFER_SIZE 1024

struct sockaddr_in server_addr;
int64_t file_size;
char buffer[BUFFER_SIZE];
int bytes_read;
char *filename;
int client_fd;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Użycie: %s <nazwa pliku>\n", argv[0]);
        exit(1);
    }

    filename = argv[1];

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Żądanie pliku: %s\n", filename);
    sprintf(buffer, "%lu", strlen(filename));
    send(client_fd, buffer, strlen(buffer), 0);
    send(client_fd, filename, strlen(filename), 0);

    recv(client_fd, buffer, sizeof(int64_t), 0);
    file_size = *(int64_t *)buffer;

    if (file_size == -1) {
        printf("Pliku nie znaleziono na serwerze.\n");
    } else {
        FILE *file = fopen(filename, "wb");

        if (file == NULL) {
            perror("fopen");
        } else {
            while (file_size > 0 && (bytes_read = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0) {
                fwrite(buffer, 1, bytes_read, file);
                file_size -= bytes_read;
            }

            fclose(file);
        }
    }

    close(client_fd);

    return 0;
}
