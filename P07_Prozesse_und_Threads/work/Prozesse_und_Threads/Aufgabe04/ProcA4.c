//***************************************************************************
// File:             ProcA4.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Demonstration paralleler Prozesse (Eltern & Kind),
//                   Simulation von CPU-Lastverhalten durch künstliche Arbeit,
//                   gebunden an CPU 0.
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Standarddatentypen wie pid_t
#include <sys/wait.h>    // Warten auf Kindprozesse (waitpid)
#include <signal.h>      // Signalverarbeitung (optional für Erweiterungen)
#include <unistd.h>      // fork(), getpid(), etc.
#include <stdio.h>       // printf(), perror(), fflush()
#include <errno.h>       // Fehlernummern für perror()
#include <stdlib.h>      // exit()

//***************************************************************************
// Lokale Includes
//***************************************************************************

#include "workerUtils.h"  // Definition von justWork(), simuliert CPU-Last
#include "selectCPU.h"    // Definition von selectCPU(), setzt CPU-Affinität

//***************************************************************************
// Definitionen
//***************************************************************************

#define ITERATIONS 20     // Anzahl der Iterationen der Arbeitsschleifen
#define WORK_HARD  2000000 // Arbeitsintensität pro Iteration

//***************************************************************************
// Funktion: main() - Startpunkt des Programms
//***************************************************************************

int main(void) {
    pid_t pid; // Prozess-ID
    int i; // Schleifenzähler

    pid = fork(); // Erzeuge einen Kindprozess

    selectCPU(0); // Binde den Prozess (egal ob Kind oder Eltern) an CPU 0

    switch (pid) {
        case -1: // Fehler beim Fork
            perror("Could not fork"); // Gibt Fehlermeldung aus
            break;

        case 0: // Kindprozess
            for (i = 0; i < ITERATIONS; i++) {
                justWork(WORK_HARD); // Simuliere Arbeitsbelastung
                printf("%d \t\tChild\n", i); // Ausgabe Iterationszähler + Rollenbezeichnung
                fflush(stdout); // Sofortige Ausgabe ohne Pufferung
            }
            break;

        default: // Elternprozess
            for (i = 0; i < ITERATIONS; i++) {
                justWork(WORK_HARD); // Simuliere Arbeitsbelastung
                printf("%d \tMother\n", i); // Ausgabe Iterationszähler + Rollenbezeichnung
                fflush(stdout); // Sofortige Ausgabe ohne Pufferung
            }
    }

    printf("I go it ...\n"); // Ausgabe nach Abschluss der jeweiligen Schleife

    if (pid > 0) // Nur der Elternprozess wartet auf das Kind
        waitpid(pid, NULL, 0); // Warten bis das Kind terminiert

    exit(0); // Programm sauber beenden
}

//***************************************************************************
