#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_LENGTH 20

// Funktion zur Umwandlung eines Strings in Großbuchstaben
void toUpperCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

// Funktion zur Überprüfung, ob ein Wort bereits im Array existiert
int isDuplicate(char words[MAX_WORDS][MAX_LENGTH], int count, char *word) {
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1; // Wort gefunden (Duplikat)
        }
    }
    return 0; // Kein Duplikat
}

// Einfacher Bubble-Sort Algorithmus zum Sortieren der Wörter
void sortWords(char words[MAX_WORDS][MAX_LENGTH], int count) {
    char temp[MAX_LENGTH];
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                // Tausche die Wörter, wenn sie in falscher Reihenfolge sind
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }
}

// Funktion zur Ausgabe aller Wörter im Array
void printWords(char words[MAX_WORDS][MAX_LENGTH], int count) {
    (void) printf("\nSortierte Wörter:\n");
    for (int i = 0; i < count; i++) {
        (void) printf("%s\n", words[i]);
    }
}

int main() {
    char words[MAX_WORDS][MAX_LENGTH] = {0}; // 2D-Array für die Wörter
    char input[MAX_LENGTH]; // Puffer für die Eingabe
    int wordCount = 0; // Zähler für gespeicherte Wörter

    (void) printf("Geben Sie bis zu %d Wörter ein (max. %d Zeichen).\n", MAX_WORDS, MAX_LENGTH - 1);
    (void) printf("Eingabeende mit 'ZZZ' oder bei Erreichen der maximalen Anzahl.\n");

    while (wordCount < MAX_WORDS) {
        (void) printf("Wort %d: ", wordCount + 1);
        scanf("%19s", input); // Begrenzt die Eingabe auf 19 Zeichen + Nullterminator

        // Überprüfe auf Abbruchbedingung
        if (strcmp(input, "ZZZ") == 0) {
            break;
        }

        // Wandle das Wort in Großbuchstaben um
        toUpperCase(input);

        // Überprüfe auf Duplikate
        if (isDuplicate(words, wordCount, input)) {
            (void) printf("Wort '%s' bereits vorhanden, wird ignoriert.\n", input);
            continue;
        }

        // Speichere das Wort im Array
        strcpy(words[wordCount], input);
        wordCount++;
    }

    // Sortiere und gib die Wörter aus
    sortWords(words, wordCount);
    printWords(words, wordCount);

    return 0;
}