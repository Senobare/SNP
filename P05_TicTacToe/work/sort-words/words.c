#include <stdio.h>
#include <string.h>

#define NUMBER_OF_WORDS        3
#define MAX_CHARS        20

void sort(char (*words)[MAX_CHARS]) {
    char temp[MAX_CHARS];

    for (int i = 0; i < NUMBER_OF_WORDS - 1; i++) {
        for (int j = 0; j < NUMBER_OF_WORDS - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                // Strings tauschen
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }
}

int main() {
    char words[NUMBER_OF_WORDS][MAX_CHARS];
    int wordCounter = 0;
    while (wordCounter < NUMBER_OF_WORDS) {
        (void) printf("%d Geben sie ein Wort mit maximal 20 Zeichen ein\n", wordCounter);
        scanf("%19s", words[wordCounter]);
        wordCounter++;
    }

    sort(words);

    for (int i = 0; i < NUMBER_OF_WORDS; i++) {
        (void) printf("%s\n", words[i]);
    }
}
