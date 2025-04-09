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

#include "person.h"
#include "list.h"

#define NAME_LEN 20

/**
 * @brief Liest eine Person von der Konsole ein.
 * 
 * Fordert den Benutzer zur Eingabe von Vorname, Nachname und Alter auf und speichert
 * die Eingabewerte in der übergebenen Person.
 * 
 * @param p [IN/OUT] Zeiger auf die Person, in der die Eingaben gespeichert werden
 * @return true, wenn die Eingabe erfolgreich war
 *         false, wenn die Eingabe fehlerhaft war
 */
bool read_person(person_t *p) {
    char buffer[NAME_LEN * 2]; // Buffer für Namen

    (void) printf("First name: ");
    if (scanf("%19s", buffer) != 1) return false; // Vorname einlesen
    strncpy(p->first_name, buffer, NAME_LEN - 1);
    p->first_name[NAME_LEN - 1] = '\0';

    (void) printf("Last name: ");
    if (scanf("%19s", buffer) != 1) return false; // Nachname einlesen
    strncpy(p->name, buffer, NAME_LEN - 1);
    p->name[NAME_LEN - 1] = '\0';

    (void) printf("Age: ");
    return scanf("%u", &p->age) == 1; // Alter einlesen
}

/**
 * @brief Main entry point.
 * @param[in] argc  The size of the argv array.
 * @param[in] argv  The command line arguments...
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) there is an expression syntax error.
 */
int main(int argc, char* argv[]) {
    char command; // Variable zur Speicherung des Benutzereingabebefehls
    person_t p;   // Struktur zur Speicherung der eingegebenen Person

    while (1) {
        (void) printf("\nI(nsert), R(emove), S(how), C(lear), Q(uit): ");
        scanf(" %c", &command); // Benutzereingabe einlesen

        switch (command) {
            case 'I': case 'i': // Einfügen
                if (read_person(&p)) {
                    if (insert_person(&p)) {
                        (void) printf("Person added successfully.\n");
                    } else {
                        (void) printf("Failed to add person.\n");
                    }
                } else {
                    (void) printf("Invalid input for person.\n");
                }
                break;

            case 'R': case 'r': // Entfernen
                if (read_person(&p)) {
                    if (remove_person(&p)) {
                        (void) printf("Person removed successfully.\n");
                    } else {
                        (void) printf("Failed to remove person.\n");
                    }
                } else {
                    (void) printf("Invalid input for person.\n");
                }
                break;

            case 'S': case 's': // Anzeigen
                show_list();
                break;

            case 'C': case 'c': // Liste leeren
                clear_list();
                (void) printf("List cleared.\n");
                break;

            case 'Q': case 'q': // Beenden
                clear_list();
                (void) printf("Exiting program.\n");
                return EXIT_SUCCESS; // Programm beenden

            default:
                (void) printf("Invalid command. Please try again.\n");
                break;
        }
    }
}