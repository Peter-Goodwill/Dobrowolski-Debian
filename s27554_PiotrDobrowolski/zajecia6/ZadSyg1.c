#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigusr1_handler(int sig_num) {
    printf("Otrzymano sygnał SIGUSR1. I release you from your bonds!\n");
    exit(0);
}

int main() {
    printf("PID: %d\n", getpid());

    if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
        return 1;
    }

    while (1) {
        pause();
    }

    return 0;
}
