#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int n;
    int i;
    int fd[2];
    int PID;
    int suma = 0;

    if (argc != 2) {
        printf("Proces \"%s\" wymaga argumentu(liczba calkowita). \n", argv[0]);
        return 1;
    }

    PID = fork();
    n = atoi(argv[1]);

    if (PID > 0) {
        close(fd[0]);

        for (i = 0; i <= n; i++) {
            suma += i;
        }
        
        wait(NULL);

        printf("Wartosc sumy od 1 do %d: %d\n", n, suma);

        close(fd[1]);
    } else {
        close(fd[1]);

        printf("Liczby nieparzyste od 1 do %d: ", n);
        for (i = 1; i <= n; i++) {
            if (i % 2 != 0) {
                printf("%d ", i);
            }
        }
        printf("\n");

        close(fd[0]);
    }

    return 0;
}
