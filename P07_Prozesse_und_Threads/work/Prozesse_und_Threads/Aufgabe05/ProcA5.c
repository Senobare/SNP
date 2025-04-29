//***************************************************************************
// File:             ProcA5.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Demonstriert den Wechsel des Elternprozesses nach
//                   Terminierung des ursprünglichen Elternprozesses.
//                   Das Kindprozess zeigt per getppid() den Übergang zur
//                   neuen Elternprozess-ID (normalerweise PID 1) und nutzt
//                   system("ps") zur Darstellung.
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Datentypen wie pid_t
#include <sys/wait.h>    // für wait()
#include <unistd.h>      // fork(), getpid(), getppid(), sleep(), usleep()
#include <stdio.h>       // printf(), perror(), sprintf()
#include <errno.h>       // Fehlerbehandlung
#include <stdlib.h>      // exit(), system()

//***************************************************************************
// Funktion: main() – Einstiegspunkt
//***************************************************************************

int main(void) {
    pid_t pid, id; // Prozess-IDs für das Eltern- und Kindprozess
    char buf[64]; // Puffer für den PS-Befehl
    int i; // Schleifenzähler

    pid = fork(); // Erzeuge ein Kindprozess

    switch (pid) {
        case -1: // Fehler beim Fork
            perror("Could not fork");
            break;

        case 0: // Kindprozess
            printf("\n... ich bin das Kind %d\n", getpid());

        // Schleife mit Ausgaben der Elternprozess-ID
            for (i = 0; i < 10; i++) {
                usleep(500000); // 0.5 Sekunden warten
                printf("Mein Elternprozess ist %d\n", id = getppid());
            }

            printf("... so das wars\n"); // Kindprozess beendet sich
            break;

        default: // Elternprozess
            sleep(12); // schläft 12 Sekunden, damit Kind aktiv bleibt
            exit(0); // beendet sich danach (Kind wird Waisenkind)
            break;
    }

    // Wird im Kindprozess nach dem Eltern-Tod ausgeführt
    printf("\n\n*** and here my new parent ****\n\n");

    // ps-Befehl vorbereiten, um neuen Elternprozess per PID anzuzeigen
    sprintf(buf, "ps -p %d", id);
    system(buf); // Befehl ausführen

    exit(0); // Prozess beenden
}

//***************************************************************************
