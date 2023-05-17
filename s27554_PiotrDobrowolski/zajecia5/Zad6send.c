#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char wiadomosc[256];

    while (1) {
        file = fopen("/tmp/chat.txt", "a");

        printf("Napisz wiadomosc: ");
        fgets(wiadomosc, sizeof(wiadomosc), stdin);
        fputs(wiadomosc, file);

        fclose(file);
    }

    return 0;
}
