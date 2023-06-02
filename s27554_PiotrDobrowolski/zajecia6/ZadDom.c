#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_PENDING 5
#define MAX_LINE 2048

void handle_request(int new_s) {
    char buf[MAX_LINE];
    const char *response;
    memset(buf, 0, sizeof(buf));
    recv(new_s, buf, sizeof(buf), 0);

    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>It works!</h1></body></html>\r\n";

    send(new_s, response, strlen(response), 0);
    close(new_s);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in sin;
    socklen_t len;
    int s;
    int new_s;

    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(1985);

    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("simplex-talk: bind");
        exit(1);
    }
    listen(s, MAX_PENDING);

    while(1) {
        if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
            perror("simplex-talk: accept");
            exit(1);
        }
        
        if(fork() == 0) {
            close(s);
            handle_request(new_s);
            exit(0);
        }
        else {
            close(new_s);
        }
    }
}

