//***************************************************************************
// File:             ProcA8_1.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Einfaches Programm zur Demonstration von fork().
//                   Zeigt, wie ein Eltern- und Kindprozess unterschiedliche
//                   Ausgaben nach einem Fork machen, wobei beide den
//                   fortgesetzten Programmfluss teilen.
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Definition von pid_t
#include <sys/wait.h>    // Funktionen wie wait(), falls später verwendet
#include <unistd.h>      // fork(), getpid()
#include <stdio.h>       // printf(), perror()
#include <errno.h>       // Fehlerbehandlung
#include <stdlib.h>      // exit()

//***************************************************************************
// Funktion: main()
// Parameter: keine
//***************************************************************************

int main(void) {

    pid_t pid;  // Prozess-ID für das neu erzeugte Kind

    printf("\n");
    printf("\nHallo, I am on the way to fork now, ......lo");

    // Erzeuge ein neues Kindprozess
    pid = fork();

    // Auswertung des Rückgabewerts von fork()
    switch (pid) {
        case -1:   // Fehler beim Forken
            perror("Could not fork");
            break;

        case 0:    // Code wird im Kindprozess ausgeführt
            printf("ok: I am the child\n");
            break;

        default:   // Code wird im Elternprozess ausgeführt
            printf("ok: I am the parent\n");
            break;
    }

    // Dieser Teil wird von beiden Prozessen erreicht
    printf("\nclear ?\n\n");

    exit(0);  // Prozess sauber beenden
}

//***************************************************************************
