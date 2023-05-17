#include <stdio.h>
#include <unistd.h>

int main() {
    int PID;
    int PPID;
    PID = getpid();
    PPID = getppid();

    printf("Process ID to:         %d \n", PID);
    printf("Parrent Process ID to: %d \n", PPID);

    return 0;
}
