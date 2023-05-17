#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void zainicjujProces(char processName) {
    int pid = fork();

    if (pid == 0) {
        printf("Proces %c zainicjowany, PID = %d, PPID = %d\n", processName, getpid(), getppid());
    }
    else {
        wait(NULL);
    }
}

int main() {
    printf("Proces MATKA: A , PID = %d\n", getpid());

    zainicjujProces('B');
    zainicjujProces('D');
    zainicjujProces('E');

    zainicjujProces('C');
    zainicjujProces('F');
    zainicjujProces('G');

    return 0;
}
