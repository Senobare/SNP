#ifndef LIST_H
#define LIST_H

#include <stdbool.h>  // Hinzugefügt, um bool zu definieren

#include "person.h"

// Struktur, die einen Knoten der verketteten Liste darstellt
// Ein Knoten enthält die Daten einer Person und einen Zeiger auf den nächsten Knoten
typedef struct node {
    person_t content;         // Person, die in diesem Knoten gespeichert ist
    struct node *next;        // Zeiger auf den nächsten Knoten in der Liste
} node_t;

// Declare anchor as extern so it can be accessed by tests
extern node_t anchor;

/**
 * @brief Fügt eine Person sortiert in die verkettete Liste ein.
 * 
 * Dabei wird die Liste so durchsucht, dass die Person an der richtigen Stelle
 * eingefügt wird, um die Liste alphabetisch und nach Alter geordnet zu halten.
 * 
 * @param p [IN] Zeiger auf die Person, die in die Liste eingefügt werden soll
 * @return true, wenn die Person erfolgreich eingefügt wurde
 *         false, wenn ein Fehler auftritt (z.B. bei Duplikaten)
 */
bool insert_person(const person_t *p);

/**
 * @brief Entfernt eine Person aus der verketteten Liste.
 * 
 * Dabei wird der Knoten, der die angegebene Person enthält, aus der Liste entfernt
 * und der entsprechende Speicher freigegeben.
 * 
 * @param p [IN] Zeiger auf die Person, die aus der Liste entfernt werden soll
 * @return true, wenn die Person gefunden und entfernt wurde
 *         false, wenn die Person nicht in der Liste gefunden wurde
 */
bool remove_person(const person_t *p);

/**
 * @brief Löscht alle Personen in der Liste und gibt den entsprechenden Speicher frei.
 */
void clear_list(void);

/**
 * @brief Gibt alle Personen in der Liste aus.
 * Die Liste wird durchlaufen und jede Person wird in der Konsole angezeigt.
 */
void show_list(void);

#endif // LIST_H
