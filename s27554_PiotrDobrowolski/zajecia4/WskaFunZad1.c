#include <stdio.h>
#include <stdlib.h>

int suma(int a, int b) { return a + b; }
int minimum(int a, int b) { return a < b ? a : b; }
int maksimum(int a, int b) { return a > b ? a : b; }

int main() {
    int (*funkcje[3])(int, int) = {suma, minimum, maksimum};

    int i;
    int v;
    int *tablica;
    int functionId;
    int elementCount;
    
    printf("Choose your funkcja DESTINY! (0 - suma, 1 - minimum, 2 - maXXXimum): ");
    scanf("%d", &functionId);

    printf("Podaj liczbe elementow: ");
    scanf("%d", &elementCount);

    tablica = (int*) malloc(elementCount * sizeof(int));
    if(tablica == NULL) {
        printf("Kapusta, tablica pusta.\n");
        return 1;
    }

    for(i = 0; i < elementCount; i++) {
        printf("Podaj %d element: ", i + 1);
        scanf("%d", &tablica[i]);
    }

    v = tablica[0];
    for(i = 1; i < elementCount; i++) {
        v = funkcje[functionId](v, tablica[i]);
    }

    printf("Wynik: %d\n", v);

    free(tablica);
    return 0;
}
