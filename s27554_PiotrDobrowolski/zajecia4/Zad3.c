#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int wysokosc;
    int i;
    int j;
    int spacja;

    if(argc != 2) {
        printf("Zadanie %s sluzy wyswietleniu choinki. Podaj parametr przy wywlaniu programu aby wyswitlic odpowiednia wysokosc.\n", argv[0]);
        return 1;
    }

    wysokosc = atoi(argv[1]);

    for(i = 1; i <= wysokosc; i++) {
           for(spacja = 0; spacja <= wysokosc - i; spacja++) {
            printf(" ");
        }
              for(j = 1; j <= 2 * i - 1; j++) {
            printf("@");
        }
        printf("\n");
    }

    return 0;
}
