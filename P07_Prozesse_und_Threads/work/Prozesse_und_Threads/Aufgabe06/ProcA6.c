//***************************************************************************
// File:             ProcA6.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Demonstriert das Erzeugen mehrerer Kindprozesse in einer
//                   Schleife. Die Elternprozess synchronisiert sich mit den
//                   Kindprozessen durch wiederholtes Aufrufen von wait().
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Standarddatentypen wie pid_t
#include <sys/wait.h>    // wait()-Funktion für Kindprozessverwaltung
#include <unistd.h>      // fork(), sleep()
#include <stdio.h>       // printf(), perror()
#include <errno.h>       // Fehlerbehandlung mit errno
#include <stdlib.h>      // exit()

//***************************************************************************
// Funktion: main() – Startpunkt des Programms
//***************************************************************************

int main(void) {

    pid_t pid;   // Prozess-ID für neue Kindprozesse
    int j;       // Schleifenzähler

    // Schleife zum Erzeugen von 3 Kindprozessen
    for (j = 0; j < 3; j++) {
        pid = fork();    // Erzeuge neuen Kindprozess

        switch (pid) {
          case -1:       // Fehler beim Fork
            perror("Could not fork");
            break;

          case 0:        // Kindprozess
            sleep(j + 2);  // Kindprozess schläft (j+2) Sekunden
                          // Kind 0: 2 Sek, Kind 1: 3 Sek, Kind 2: 4 Sek
            exit(0);     // Nach dem Schlafen beendet sich das Kind
            break;

          default:       // Elternprozess
            // Elternprozess tut in der Schleife nichts weiter
            break;
        }
    }

    // Elternprozess-Code nach dem Erzeugen aller Kinder

    sleep(8);    // Elternprozess schläft 8 Sekunden (wartet auf Kindprozesse)

    wait(NULL);  // Warten auf ein beendetes Kind
    sleep(2);    // Nach jedem Warten nochmal schlafen (2 Sekunde Pause)

    wait(NULL);  // Warten auf das nächste beendete Kind
    sleep(2);

    wait(NULL);  // Warten auf das letzte beendete Kind
    sleep(2);

    exit(0);     // Elternprozess beendet sich
}
