/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>

#define NAME_LEN 20

typedef struct {
    char name[NAME_LEN];
    char first_name[NAME_LEN];
    unsigned int age;
} person_t;

typedef struct node {
    person_t content;
    struct node *next;
} node_t;

// Initialisierung der zyklisch verketteten Liste
static node_t anchor = { .next = &anchor };

/* 
 * Vergleicht zwei Personen nach Name, Vorname und Alter
 * @return <0 wenn a < b, 0 wenn gleich, >0 wenn a > b
 */
int person_compare(const person_t *a, const person_t *b) {
    int cmp = strncmp(a->name, b->name, NAME_LEN);
    if (cmp != 0) return cmp;
    cmp = strncmp(a->first_name, b->first_name, NAME_LEN);
    if (cmp != 0) return cmp;
    return (int)a->age - (int)b->age;
}

/*
 * Prüft ob eine Person bereits in der Liste existiert
 * @return true wenn Person existiert, sonst false
 */
bool is_duplicate(const person_t *p) {
    node_t *current = anchor.next;
    while (current != &anchor) {
        if (person_compare(&current->content, p) == 0) return true;
        current = current->next;
    }
    return false;
}

/*
 * Fügt eine Person sortiert in die Liste ein
 * @return true bei Erfolg, false bei Fehler
 */
bool insert_person(const person_t *p) {
    if (is_duplicate(p)) {
        printf("Error: Person already exists\n");
        return false;
    }

    // Speicher für neuen Knoten allozieren
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) return false;
    memcpy(&new_node->content, p, sizeof(person_t));

    // Richtige Einfügeposition suchen (sortiert)
    node_t *prev = &anchor;
    node_t *current = anchor.next;
    while (current != &anchor && person_compare(&current->content, p) < 0) {
        prev = current;
        current = current->next;
    }

    // Knoten einfügen
    prev->next = new_node;
    new_node->next = current;
    return true;
}

/*
 * Entfernt eine Person aus der Liste
 * @return true wenn Person gefunden und entfernt wurde
 */
bool remove_person(const person_t *p) {
    node_t *prev = &anchor;
    node_t *current = anchor.next;
    while (current != &anchor) {
        if (person_compare(&current->content, p) == 0) {
            prev->next = current->next;
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    printf("Error: Person not found\n");
    return false;
}

/*
 * Leert die gesamte Liste und gibt den Speicher frei
 */
void clear_list() {
    node_t *current = anchor.next;
    while (current != &anchor) {
        node_t *next = current->next;
        free(current);
        current = next;
    }
    anchor.next = &anchor;  // Liste auf Anfangszustand zurücksetzen
}

/*
 * Zeigt alle Personen in der Liste an
 */
void show_list() {
    node_t *current = anchor.next;
    while (current != &anchor) {
        printf("%s %s, %u\n", current->content.first_name, 
               current->content.name, current->content.age);
        current = current->next;
    }
}

/*
 * Liest Personendaten von der Konsole ein
 * @return true bei erfolgreicher Eingabe
 */
bool read_person(person_t *p) {
    char buffer[NAME_LEN * 2];  // Puffer für sichere Eingabe

    printf("First name: ");
    if (scanf("%19s", buffer) != 1) return false;
    strncpy(p->first_name, buffer, NAME_LEN - 1);
    p->first_name[NAME_LEN - 1] = '\0';

    printf("Last name: ");
    if (scanf("%19s", buffer) != 1) return false;
    strncpy(p->name, buffer, NAME_LEN - 1);
    p->name[NAME_LEN - 1] = '\0';

    printf("Age: ");
    return scanf("%u", &p->age) == 1;
}

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
 */
int main(int argc, char* argv[])
{
    // Deklaration der Variablen
    char command;  // Speichert den Benutzerbefehl (I,R,S,C,E)
    person_t p;    // Temporäre Speicherung der Personendaten

    // Hauptprogrammschleife
    while (1) {
        printf("\nI(nsert), R(emove), S(how), C(lear), E(nd): ");
        if (scanf(" %c", &command) != 1) {
            printf("Invalid input\n");
            while(getchar() != '\n');
            continue;
        }

        switch (command) {
            case 'I': case 'i':  // Person einfügen
                if (!read_person(&p)) {
                    printf("Invalid input\n");
                    while(getchar() != '\n');  // Eingabepuffer leeren
                    break;
                }
                insert_person(&p);
                break;

            case 'R': case 'r':  // Person entfernen
                if (!read_person(&p)) {
                    printf("Invalid input\n");
                    while(getchar() != '\n');
                    break;
                }
                remove_person(&p);
                break;

            case 'S': case 's':  // Liste anzeigen
                show_list();
                break;

            case 'C': case 'c':  // Liste leeren
                clear_list();
                break;

            case 'E': case 'e':  // Programm beenden
                clear_list();
                return EXIT_SUCCESS;

            default:  // Ungültige Eingabe
                printf("Invalid command\n");
        }
    }

    return EXIT_SUCCESS;
}
