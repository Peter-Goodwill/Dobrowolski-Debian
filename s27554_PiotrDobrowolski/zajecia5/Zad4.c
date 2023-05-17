#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i;
    int PID;
    const int procPotomny = 100;

    for (i = 0; i < procPotomny; i++) {
        PID = fork();

        if (PID == 0) {
            printf("Proces potomny: PID %d, PPID %d\n", getpid(), getppid());
        } else {
            wait(NULL);
            break;
        }
    }

    return 0;
}
