#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

#define LOCK_FILE "/tmp/lock"

void handle_sigusr1(int sig) {
    printf("Wykryto probe uruchomienia drugiej instancji programu. \n");
}

void handle_sigint(int sig) {
    printf("\nKonczenie programu. \n");
    if (remove(LOCK_FILE) == 0)
        printf("Usunieto plik blokady. \n");
    else
        printf("Nie udalo sie usunac pliku blokady. \n");

    exit(0);
}

int main() {
    int lock_file;
    int pid;
    char pid_string[20];

    signal(SIGUSR1, handle_sigusr1);
    signal(SIGINT, handle_sigint);

    lock_file = open(LOCK_FILE, O_RDONLY);
    if (lock_file == -1) {
        lock_file = open(LOCK_FILE, O_WRONLY | O_CREAT, 0644);
        if (lock_file == -1) {
            perror("Blad przy tworzeniu pliku blokady.");
            exit(1);
        }
        sprintf(pid_string, "%d", getpid());
        write(lock_file, pid_string, strlen(pid_string));
        close(lock_file);
        printf("Utworzono plik blokady z PID: %d\n", getpid());

        while (1) {
            sleep(1);
        }
    } else {
        read(lock_file, pid_string, sizeof(pid_string));
        pid = atoi(pid_string);
        close(lock_file);
        printf("Wykryto dzialajaca instancje programu z PID: %d. Wysylanie sygnalu SIGUSR1. \n", pid);
        kill(pid, SIGUSR1);
    }

    return (0);
}
