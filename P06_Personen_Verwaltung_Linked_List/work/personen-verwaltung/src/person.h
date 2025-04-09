#ifndef PERSON_H
#define PERSON_H

// Definition der Konstanten für die maximale Länge eines Namens
#define NAME_LEN 20

// Struktur, die eine Person repräsentiert
// Sie enthält Vorname, Nachname und Alter
typedef struct {
    char name[NAME_LEN];       // Nachname der Person
    char first_name[NAME_LEN]; // Vorname der Person
    unsigned int age;          // Alter der Person
} person_t;

/**
 * @brief Vergleicht zwei Personen basierend auf ihrem Namen, Vornamen und Alter.
 * 
 * Die Reihenfolge der Vergleiche ist wie folgt:
 * 1. Nachname
 * 2. Vorname
 * 3. Alter
 * 
 * @param a [IN] Zeiger auf die erste Person für den Vergleich
 * @param b [IN] Zeiger auf die zweite Person für den Vergleich
 * 
 * @return 0, wenn alle Felder identisch sind
 *         >0, wenn das erste differierende Feld bei der ersten Person größer ist
 *         <0, wenn das erste differierende Feld bei der zweiten Person größer ist
 */
int person_compare(const person_t *a, const person_t *b);

#endif // PERSON_H
