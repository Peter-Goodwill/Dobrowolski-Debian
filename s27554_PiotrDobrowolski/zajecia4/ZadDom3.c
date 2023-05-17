#include <stdio.h>

int fibonacci_rekurencyjnie(int n) {
    if(n <= 1) {
        return n;
    }
    else {
        return fibonacci_rekurencyjnie(n-1) + fibonacci_rekurencyjnie(n-2);
    }
}

int fibonacci_iteracyjnie(int n) {
    int i;
    int n1 = 0;
    int n2 = 1;
    int n3 = 0;

    for (i = 1; i <= n; ++i) {
        if(i == 1) {
            n3 = n1;
        }
        else if(i == 2) {
            n3 = n2;
        }
        else {
            n3 = n1 + n2;
            n1 = n2;
            n2 = n3;
        }
    }
    return n3;
}

int main() {
    int n = 0;

    printf("Podaj cyfre do obliczenia liczby Fibonacciego: ");
    scanf("%d", &n);

    printf("Rekurencyjny ciąg Fibonacciego dla %d wynosi %d.\n", n, fibonacci_rekurencyjnie(n));
    printf("Iteracyjny ciąg Fibonacciego dla %d wynosi %d.\n", n, fibonacci_iteracyjnie(n));

    return 0;
}
