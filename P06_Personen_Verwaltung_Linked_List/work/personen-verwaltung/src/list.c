#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>  // Hinzugefügt, um bool zu definieren

// Initialisierung des Ankers der zyklisch verketteten Liste
node_t anchor = { .next = &anchor }; // Der Anker zeigt immer auf sich selbst

/**
 * @brief Prüft, ob die Person bereits in der Liste existiert.
 * 
 * Dies wird durch einen Vergleich der Person mit allen bestehenden Personen in der Liste
 * erreicht. Wenn die Person bereits vorhanden ist, wird true zurückgegeben.
 * 
 * @param p [IN] Zeiger auf die zu prüfende Person
 * @return true, wenn die Person bereits in der Liste vorhanden ist
 *         false, wenn die Person nicht in der Liste vorhanden ist
 */
bool is_duplicate(const person_t *p) {
    node_t *current = anchor.next;
    while (current != &anchor) { // Durchlaufe die Liste bis zum Anker
        if (person_compare(&current->content, p) == 0) return true; // Duplikat gefunden
        current = current->next;
    }
    return false; // Kein Duplikat
}

/**
 * @brief Fügt eine neue Person in die verkettete Liste ein.
 * 
 * Die Liste wird durchsucht, um den richtigen Platz für die Person zu finden, wobei
 * die Liste in alphabetischer Reihenfolge nach Nachname, Vorname und Alter geordnet wird.
 * 
 * @param p [IN] Zeiger auf die Person, die eingefügt werden soll
 * @return true, wenn die Person erfolgreich eingefügt wurde
 *         false, wenn ein Fehler auftritt (z.B. Duplikat)
 */
bool insert_person(const person_t *p) {
    if (is_duplicate(p)) {
        printf("Error: Person already exists\n");
        return false; // Person existiert bereits
    }

    node_t *new_node = malloc(sizeof(node_t)); // Speicher für neuen Knoten anfordern
    if (!new_node) return false; // Fehler bei der Speicherzuweisung

    memcpy(&new_node->content, p, sizeof(person_t)); // Person kopieren

    node_t *prev = &anchor; // Anker als Startpunkt
    node_t *current = anchor.next;
    
    // Suche die richtige Stelle für das Einfügen
    while (current != &anchor && person_compare(&current->content, p) < 0) {
        prev = current;
        current = current->next;
    }

    prev->next = new_node;  // Füge den neuen Knoten in die Liste ein
    new_node->next = current; // Der neue Knoten zeigt auf den nächsten Knoten
    return true; // Erfolgreiches Einfügen
}

/**
 * @brief Entfernt eine Person aus der verketteten Liste.
 * 
 * Die Liste wird durchsucht und der Knoten, der die angegebene Person enthält, wird entfernt.
 * Der Speicher wird dabei freigegeben.
 * 
 * @param p [IN] Zeiger auf die zu entfernende Person
 * @return true, wenn die Person gefunden und entfernt wurde
 *         false, wenn die Person nicht gefunden wurde
 */
bool remove_person(const person_t *p) {
    node_t *prev = &anchor;
    node_t *current = anchor.next;
    
    // Suche nach dem Knoten, der die Person enthält
    while (current != &anchor) {
        if (person_compare(&current->content, p) == 0) {
            prev->next = current->next; // Verknüpfe den vorherigen Knoten mit dem nächsten
            free(current); // Speicher des entfernten Knotens freigeben
            return true;
        }
        prev = current;
        current = current->next;
    }
    printf("Error: Person not found\n");
    return false; // Person nicht gefunden
}

/**
 * @brief Löscht alle Knoten in der Liste und gibt den Speicher frei.
 * 
 * Diese Funktion wird aufgerufen, um alle Personen zu entfernen und den gesamten Speicher
 * der Liste freizugeben.
 */
void clear_list(void) {
    node_t *current = anchor.next;
    while (current != &anchor) { // Durchlaufe die Liste
        node_t *next = current->next;
        free(current); // Speicher freigeben
        current = next;
    }
    anchor.next = &anchor; // Anker zurücksetzen
}

/**
 * @brief Gibt alle Personen in der Liste aus.
 * 
 * Diese Funktion durchläuft die Liste und gibt die Namen und das Alter jeder Person aus.
 */
void show_list(void) {
    node_t *current = anchor.next;
    while (current != &anchor) { // Durchlaufe die Liste
        printf("%s %s, %u\n", current->content.first_name, 
               current->content.name, current->content.age);
        current = current->next;
    }
}
