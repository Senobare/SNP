/*********************************************************************
* File:            MrTimeDaemon.c
* Original Autor:  M. Thaler (Modul BSY)
* Aufgabe:         Einen Daemon-Prozess erzeugen
*
* Beschreibung:
* Dieses Programm startet einen Hintergrunddienst ("Daemon"), der in
* einem eigenen Prozess im Hintergrund läuft, unabhängig vom Terminal.
* Die Initialisierung und Abtrennung vom Terminal übernimmt die Funktion
* `Daemonizer()`. Die eigentliche Logik des Daemons liegt in `TimeDaemon()`.
*********************************************************************/

#include <stdio.h>        // für printf
#include <assert.h>       // für assert()
#include <stdlib.h>       // für exit()
#include <unistd.h>       // für fork(), getpid(), etc.
#include <sys/wait.h>     // für wait()
#include <sys/types.h>    // für pid_t

#include "Daemonizer.h"   // eigene Hilfsfunktion zum Erzeugen eines Daemons
#include "TimeDaemon.h"   // enthält die eigentliche Arbeitsroutine für den Daemon

#define STRING_LENGTH 128

//--------------------------------------------------------------------

int main(void) {
    pid_t pid;                          // Prozess-ID für Kindprozess
    int status;                         // Rückgabestatus
    const char *lockfilePath = "/tmp/timeDaemon.lock";   // Lockfile zum Schutz vor Mehrfachstart
    // const char *lockfilePath = NULL; // Alternative: kein Lockfile
    const char *logfilePath  = "/tmp/timeDaemon.log";    // Log-Datei für Ausgaben des Daemons
    const char *livingPath   = "/tmp";                   // Arbeitsverzeichnis des Daemons
    const char *myName       = "I am Mr. Time Daemon on \n";  // Übergabeparameter an Daemon-Funktion

    // Starte Kindprozess, der Daemon erzeugt
    if ((pid = fork()) == 0)
        // Im Kindprozess:
        // Starte Daemonizer, übergebe:
        // - Funktionszeiger auf TimeDaemon
        // - Parameter (myName)
        // - Lockfile zur Mehrfachsicherung
        // - Logfile für Ausgaben
        // - Ziel-Arbeitsverzeichnis
        Daemonizer(TimeDaemon, (void *)myName,
                            lockfilePath, logfilePath, livingPath);

    else {
        // Im Elternprozess:
        assert(pid > 0);            // Sicherstellen, dass fork erfolgreich war
        wait(&status);              // Warte auf Ende von Daemonizer (nicht des Daemons!)
                                    // Daemonizer forkt selbst noch den echten Daemon
        if (WEXITSTATUS(status) != 0)
            printf("*** Daemonizer failed ***\n");  // Fehlerbehandlung
    }

    return 0;
}

//--------------------------------------------------------------------
