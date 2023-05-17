#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE *file;
    char wiadomosc[256];

    while (1) {
        file = fopen("/tmp/chat.txt", "r");

        while (fgets(wiadomosc, sizeof(wiadomosc), file)) {
            printf("%s", wiadomosc);
        }

        fclose(file);
        sleep(10);
    }

    return 0;
}
