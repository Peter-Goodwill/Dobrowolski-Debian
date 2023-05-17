#include <stdio.h>

int main() {
    int n;
    int i;
    int liczba;
    int suma;
    suma = 0;

    printf("Podaj liczbe liczb(do zsumowania): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Wprowadz %d liczbe: ", i + 1);
        scanf("%d", &liczba);
        suma += liczba;
    }

    printf("Suma wynosi %d\n", suma);
    return 0;
}
