#include <stdlib.h>
#include <stdio.h>

void print_bits(char c) {
    for (int i = 7; i >= 0; i--) {
        (void) printf("%d", (c >> i) & 1);
    }
    (void) printf("\n");
}

// Dies Funktioniert da die abfolge der Bits die gleiche ist bis auf Stelle 5.
// welche bei kleinbuchstaben eine 0 ist
// und bei grossbuchstaben eine 1
int main() {
    char word[8] = "sREedEv";
    char *wordptr = &word[0];

    while (wordptr < &word[7]) {
        (void) printf("Original char: %c | Binary: ", *wordptr);
        print_bits(*wordptr);

        (void) printf("UPPERCASE: %c\n", *wordptr & '_'); // converts the char into uppercase regardless of the current casing
        print_bits(*wordptr & '_');
        (void) printf("LOWERCASE: %c\n", *wordptr | ' '); // converts the char into lowercase regardless of the current casing
        print_bits(*wordptr | ' ');
        wordptr++;
        (void) printf("\n");
    }

    return EXIT_SUCCESS;
}
