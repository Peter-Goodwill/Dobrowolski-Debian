#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int PID;
    PID = fork();

    if (PID == 0) {
        printf("Proces potomka - PID: %d, PPID:        %d\n", getpid(), getppid());
    } else {
        wait(NULL);
        printf("Proces rodzica - PID: %d, Child's PID: %d\n", getpid(), PID);
    }

    return 0;
}
