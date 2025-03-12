#include <stdio.h>
#include <stdlib.h>

int main(){
    int a = 32; // any positive number

    // 100000 (32)
    // -1 = 011111 (31)
    // Bei & stimmt keine 1 überein deswegen ist das ergebnis = 000000 und somit 0

    // 10101 (21)
    // -1 = 10100 (20)
    // Bei & stimmen zwei 1 überein deswegen ist das ergebnis = 10100 und somit (20) und deswegen false

    if(a > 0 && (a & a - 1) == 0){
        (void) printf("%d is a power of 2", a);
    }

    return EXIT_SUCCESS;
}