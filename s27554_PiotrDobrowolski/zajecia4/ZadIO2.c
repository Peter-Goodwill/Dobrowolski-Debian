#include <stdio.h>

#define BAJTY_NA_LINIE 16

int main(int argc, char *argv[]) {
    FILE *plik;
    unsigned char bajt;
    int licznik = 0;

    if(argc != 2) {
        printf("Użycie: %s [nazwa pliku]\n", argv[0]);
        return 1;
    }

    plik = fopen(argv[1], "rb");
    if(plik == NULL) {
        printf("Błąd otwarcia pliku %s", argv[1]);
        return 1;
    }

    while(fread(&bajt, sizeof(unsigned char), 1, plik)) {
        printf(" %02x ", bajt);
        if(++licznik % BAJTY_NA_LINIE == 0) {
            printf(" \n");
        }
    }

    fclose(plik);
    return 0;
}
