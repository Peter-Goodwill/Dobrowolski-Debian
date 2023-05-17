#include <stdio.h>
#include <stdlib.h>

int suma(int a, int b) { return a + b; }
int minimum(int a, int b) { return a < b ? a : b; }
int maksimum(int a, int b) { return a > b ? a : b; }

int forAll(int* tablica, int liczbaElementow, int (*f)(int, int)) {
    int i;
    int v = tablica[0];
    for(i = 1; i < liczbaElementow; i++) {
        v = f(v, tablica[i]);
    }
    return v;
}

int main() {
    int tablica[] = {1, 2, 3, 4, 5};
    int liczbaElementow = sizeof(tablica) / sizeof(tablica[0]);

    int wynik = forAll(tablica, liczbaElementow, maksimum);
    printf("Maksimum wynosi: %d\n", wynik);

    wynik = forAll(tablica, liczbaElementow, minimum);
    printf("Minimum wynosi: %d\n", wynik);

    wynik = forAll(tablica, liczbaElementow, suma);
    printf("Suma wynosi: %d\n", wynik);

    return 0;
}
