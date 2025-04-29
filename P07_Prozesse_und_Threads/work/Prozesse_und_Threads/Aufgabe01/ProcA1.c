//***************************************************************************
// File:             ProcA1.c
// Original Author:  M. Thaler (Modul BSY)
//***************************************************************************

//***************************************************************************
// system includes
//***************************************************************************

#include <sys/types.h>  // Datentypen wie pid_t
#include <sys/wait.h>   // wait()-Funktion, um auf Kindprozess zu warten
#include <unistd.h>     // fork(), getpid(), getppid()
#include <stdio.h>      // printf(), perror()
#include <errno.h>      // Fehlerbehandlung mit errno
#include <stdlib.h>     // exit()

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    pid_t  pid;      // Prozess-ID
    int    status;   // Variable für den Rückgabewert von wait()
    int    i;        // Testvariable zur Beobachtung von Prozesskopien

    i = 5;           // Initialisierung der Variable i

    printf("\n\ni vor fork: %d\n\n", i);  // Ausgabe von i vor dem Fork

    pid = fork();    // Erzeugt einen neuen (Kind-)Prozess

    switch (pid) {
      case -1: // Fehler beim Fork
        perror("Could not fork");  // Gibt eine Fehlermeldung aus
        break;

      case 0:  // Kindprozess-Zweig
        i++;   // i im Kindprozess wird inkrementiert
        printf("\n... ich bin das Kind %d mit i=%d, ", getpid(), i);
        printf("meine Eltern sind %d \n", getppid());
        break;

      default:  // Elternprozess-Zweig
        i--;   // i im Elternprozess wird dekrementiert
        printf("\n... wir sind die Eltern %d mit i=%d ", getpid(), i);
        printf("und Kind %d,\n    unsere Eltern sind %d\n", pid, getppid());
        wait(&status);  // Warten, bis das Kind beendet ist
        break;
    }

    // Wird sowohl im Kind- als auch im Elternprozess ausgeführt
    printf("\n. . . . . und wer bin ich ?\n Ich bin %d \n", getpid());

    exit(0);  // Beendet den jeweiligen Prozess
}

//***************************************************************************
