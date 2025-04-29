//***************************************************************************
// File:             ChildProcA7.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Dieses Programm simuliert verschiedene Verhaltensweisen
//                   eines Kindprozesses, basierend auf einem übergebenen
//                   Parameter (argv[1]).
//                   Je nach Wert von i erzeugt das Programm verschiedene
//                   normale oder fehlerhafte Terminierungen.
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Standarddatentypen wie pid_t
#include <sys/wait.h>    // Warten auf Kindprozesse (wait)
#include <unistd.h>      // fork(), getpid(), sleep()
#include <stdio.h>       // printf()
#include <errno.h>       // Fehlerbehandlung
#include <stdlib.h>      // exit(), atoi()
#include <signal.h>      // Signalbehandlung, kill()

//***************************************************************************
// Funktion: main()
// Parameter:
//    argc - Argument count
//    argv - Argument vector (argv[0]: Programmname, argv[1]: Nummer i)
//***************************************************************************

int main(int argc, char *argv[]) {

    int i = 0, *a = NULL;   // i = Jobnummer, a = Null-Pointer für absichtlichen Fehler

    // Prüfen, ob ein Argument übergeben wurde
    if (argc > 1)
        i = atoi(argv[1]);  // String argv[1] in eine ganze Zahl i umwandeln

    printf("\n*** I am the child having job nr. %d ***\n\n", i);

    // Verhalten je nach Wert von i
    switch(i) {
        case 0:
            // Normales Beenden ohne Fehler
            exit(0);
            break;

        case 1:
            // Absichtlicher Segmentation Fault durch Dereferenzierung eines NULL-Pointers
            *a = i;
            break;

        case 2:
            // Prozess sendet sich selbst das Signal 30 (Benutzerdefiniertes Signal)
            kill(getpid(), 30);
            break;

        case 3:
            // Prozess schläft 5 Sekunden, wartet auf ein Signal
            sleep(5);
            break;

        case 4:
            // Prozess schläft 5 Sekunden und beendet sich dann mit Exit-Code 222
            sleep(5);
            exit(222);
            break;

        default:
            // Bei ungültigem Wert von i beendet sich der Prozess mit Fehlercode -1
            exit(-1);
    }

    // Sicherheitshalber Exit-Aufruf (wird bei korrekter Ausführung des Switch-Blocks nie erreicht)
    exit(0);
}

//***************************************************************************
