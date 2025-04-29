//***************************************************************************
// File:             ProcA8_3.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Demonstriert konkurrierendes Schreiben in eine Datei
//                   durch Eltern- und Kindprozess nach einem fork().
//                   Zusätzlich wird die CPU absichtlich belastet, um
//                   Kontextwechsel (Task-Switches) zu provozieren.
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Datentypen wie pid_t
#include <sys/wait.h>    // Funktionen wie waitpid()
#include <unistd.h>      // fork(), usleep()
#include <stdio.h>       // printf(), perror(), fopen(), fprintf(), fflush()
#include <errno.h>       // Fehlerbehandlung
#include <stdlib.h>      // exit()
#include <sched.h>       // (hier eingebunden, aber nicht direkt verwendet)

//***************************************************************************
// Lokale Includes
//***************************************************************************

#include "workerUtils.h" // Enthält Funktionen launchWorkLoad(), justWork(), stopWorkLoad()

//***************************************************************************
// Definitionen
//***************************************************************************

#define ANZAHL      15        // Anzahl der Schleifendurchläufe
#define WORK_HARD   1000000    // Simulierte Arbeitslast pro Iteration

//***************************************************************************
// Funktion: main()
// Parameter: keine
//***************************************************************************

int main(void) {

    FILE   *fdes;    // Dateideskriptor für Dateioperationen
    pid_t  pid;      // Prozess-ID für Kindprozess
    int    i;        // Schleifenzähler

    launchWorkLoad();    // Startet eine künstliche CPU-Last zur Erzeugung von Kontextwechseln

    // Datei zum Schreiben öffnen
    fdes = fopen("AnyOutPut.txt", "w");
    if (fdes == NULL)
        perror("Cannot open file"); // Fehlerbehandlung bei Dateifehler

    usleep(500000);    // kurze Verzögerung, damit die CPU-Last aufgebaut ist

    pid = fork();      // Erzeuge Kindprozess

    switch (pid) {
        case -1:       // Fehler beim fork()
            perror("Could not fork");
            break;

        case 0:        // Kindprozess
            for (i = 1; i <= ANZAHL; i++) {
                fprintf(fdes, "Fritzli\t%d\n", i); // In Datei schreiben
                fflush(fdes);                     // Direkt in Datei schreiben, Puffer leeren
                justWork(WORK_HARD);               // CPU-Last erzeugen
            }
            break;

        default:       // Elternprozess
            for (i = 1; i <= ANZAHL; i++) {
                fprintf(fdes, "Mami\t%d\n", i);    // In Datei schreiben
                fflush(fdes);                     // Direkt in Datei schreiben, Puffer leeren
                justWork(WORK_HARD);               // CPU-Last erzeugen
            }
            fflush(stdout);   // Terminalausgabe-Puffer leeren
            stopWorkLoad();   // CPU-Last stoppen
            break;
    }

    printf("We are done\n"); // Abschlussmeldung

    if (pid > 0) {
        waitpid(pid, NULL, 0);  // Elternprozess wartet auf Kindprozess
        printf("See file AnyOutPut.txt\n"); // Hinweis auf die Ausgabedatei
    }

    fflush(stdout);   // Sicherheitshalber Ausgabe beenden
    exit(0);          // Programm sauber beenden
}

//*****************************************************************************
