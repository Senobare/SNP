#include <stdlib.h>
#include <stdio.h>

int main() {
    int a = 3;
    int b = 4;
    (void) printf("a: %d; b: %d\n", a, b);

    int temp = a;
    a = b;
    b = temp;

    (void) printf("a: %d; b: %d\n", a, b);

    a = a ^ b; // 011 ^ 100 = 111
    b = a ^ b; // 111 ^ 100 = 011
    a = a ^ b; // 111 ^ 011 = 100

    (void) printf("After swap: a = %d, b = %d\n", a, b);

    return EXIT_SUCCESS;
}
