#include "person.h"
#include <string.h>

/**
 * @brief Vergleicht zwei Personen nach Namen, Vornamen und Alter.
 * 
 * Diese Funktion wird verwendet, um zwei Personen zu vergleichen, wobei zuerst der
 * Nachname, dann der Vorname und schließlich das Alter berücksichtigt wird.
 * 
 * @param a [IN] Zeiger auf die erste Person
 * @param b [IN] Zeiger auf die zweite Person
 * 
 * @return 0, wenn alle Felder gleich sind
 *         >0, wenn das erste differierende Feld bei der ersten Person größer ist
 *         <0, wenn das erste differierende Feld bei der zweiten Person größer ist
 */
int person_compare(const person_t *a, const person_t *b) {
    int cmp = strncmp(a->name, b->name, NAME_LEN); // Vergleich der Nachnamen
    if (cmp != 0) return cmp; // Rückgabe, wenn Nachnamen unterschiedlich sind

    cmp = strncmp(a->first_name, b->first_name, NAME_LEN); // Vergleich der Vornamen
    if (cmp != 0) return cmp; // Rückgabe, wenn Vornamen unterschiedlich sind

    return (int)a->age - (int)b->age; // Vergleich des Alters
}
