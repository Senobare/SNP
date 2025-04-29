//***************************************************************************
// File:             ProcA2.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Demonstriert Prozess-Erzeugung mit fork() und anschließender
//                   Programmausführung im Kindprozess mit execl().
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>  // Enthält Datentypen wie pid_t
#include <sys/wait.h>   // Für wait()
#include <unistd.h>     // Enthält fork(), execl(), getpid(), getppid()
#include <stdio.h>      // printf(), perror(), sprintf()
#include <errno.h>      // Fehlercodes für perror()
#include <stdlib.h>     // exit()

//***************************************************************************
// Funktion: main()
//***************************************************************************

int main(void) {
    pid_t pid; // Prozess-ID
    int status; // Rückgabewert von wait()
    int i, retval; // Zählvariable und Rückgabewert von execl()
    char str[8]; // Zeichenarray zur Übergabe des Parameters an execl()

    i = 5; // Initialisierung der Zählvariable

    printf("\n\ni vor fork: %d\n\n", i);

    pid = fork(); // Erzeugt einen neuen Kindprozess

    switch (pid) {
        case -1: // Fehlerfall beim Fork
            perror("Could not fork");
            break;

        case 0: // Kindprozess
            i++; // Erhöhe i auf 6
            sprintf(str, "%d", i); // Konvertiere i in einen String (z. B. "6")

        // execl ersetzt den aktuellen Kindprozess durch ein neues Programm
        // Aufruf: execl(pfad, arg0, arg1, ..., NULL)
        // arg0 = Name des Programms (üblicherweise gleich wie der Pfad oder basename)
        // arg1 = erster Parameter (hier: der Wert von i als String)
        // NULL = Abschluss der Argumentliste
            retval = execl("./ChildProcA2.e", "ChildProcA2.e", str, NULL);

        // Falls execl fehlschlägt, wird folgender Code noch ausgeführt:
            if (retval < 0) perror("\nexecl not successful");
            break;

        default: // Elternprozess
            i--; // Verringere i auf 4
            printf("\n... wir sind die Eltern %d mit i=%d ", getpid(), i);
            printf("und Kind %d,\n    unsere Eltern sind %d\n", pid, getppid());
            wait(&status); // Warten, bis das Kindprogramm beendet ist
            break;
    }

    // Wird nur ausgeführt, wenn execl NICHT erfolgreich war (z. B. im Elternprozess)
    // oder falls execl im Kindprozess fehlschlägt.
    printf("\n. . . . . und wer bin ich ?\n Ich bin %d \n", getpid());

    exit(0);
}
