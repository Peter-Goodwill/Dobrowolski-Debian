#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *plik;
    int i;
    int n;
    int *tablica;

    if(argc == 1) {
        plik = stdin;
    } else if(argc == 2) {
        plik = fopen(argv[1], "r");
        if(plik == NULL) {
            printf("Blad otwarcia pliku %s\n", argv[1]);
            return 1;
        } 
    } else {
        printf("Otwierasz %s, podaj argument, glupcze.", argv[0]);
        return 1;
    }

    if(fscanf(plik, "%d", &n) != 1) {
        printf("Blad odczytu liczby elementow\n");
        if(argc == 2) fclose(plik);
        return 1;
    }

    tablica = (int*) malloc(n * sizeof(int));
    if(tablica == NULL) {
        printf("Blad alokacji pamieci\n");
        if(argc == 2) fclose(plik);
        return 1;
    }

    for(i = 0; i < n; i++) {
        if(fscanf(plik, "%d", &tablica[i]) != 1) {
            printf("Blad odczytu liczby.\n");
            free(tablica);
            if(argc ==2) fclose(plik);
            return 1;
        }
    }

    for(i = n - 1; i >= 0; i--) {
        printf("%d\n", tablica[i]);
    }

    free(tablica);
    if(argc == 2) fclose(plik);

    return 0;
}
