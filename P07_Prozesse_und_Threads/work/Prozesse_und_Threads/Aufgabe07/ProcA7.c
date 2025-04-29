//***************************************************************************
// File:             ProcA7.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Dieses Programm startet einen Kindprozess mit einem
//                   definierten Verhalten (gesteuert durch Argument `argv[1]`).
//                   Der Kindprozess wird per `execl()` durch das Programm
//                   `ChildProcA7.e` ersetzt. Der Elternprozess wartet dann auf
//                   den Kindprozess und analysiert dessen Beendigungsgrund.
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Datentypen wie pid_t
#include <sys/wait.h>    // wait(), waitpid()
#include <unistd.h>      // fork(), execl(), sleep(), usleep()
#include <stdio.h>       // printf(), perror(), sprintf()
#include <errno.h>       // Fehlercodes
#include <stdlib.h>      // exit(), atoi()
#include <signal.h>


//***************************************************************************
// Funktion: main()
// Parameter:
//   argc, argv – argv[1] bestimmt das Verhalten des Kindprozesses
//***************************************************************************

int main(int argc, char *argv[]) {
    pid_t  pid;                 // Prozess-ID des Kindes
    int    status;              // Rückgabewert von wait/waitpid
    int    retval;              // Rückgabewert von execl()
    int    whatToDo = 0;        // Steuerwert für das Kindverhalten
    char   str[8];              // Übergabepuffer für execl()

    // Auslesen des Steuerparameters (optional)
    if (argc > 1)
        whatToDo = atoi(argv[1]);

    pid = fork();  // Kindprozess erzeugen

    switch (pid) {
      case -1:
        perror("Could not fork");  // Fehler beim Fork
        break;

      case 0:  // Kindprozess-Zweig
        sprintf(str, "%d", whatToDo);  // wandelt Steuerwert in String
        retval = execl("./ChildProcA7.e", "ChildProcA7.e", str, NULL); // Programm ersetzen
        if (retval < 0)
            perror("\nexecl not successful");  // falls execl fehlschlägt
        break;

      default:  // Elternprozess-Zweig
        if (whatToDo <= 3) {
            if (whatToDo == 3) {
                sleep(1);                    // kurz warten, damit Kind läuft
                kill(pid, SIGABRT);          // versuche, Kindprozess mit SIGABRT zu beenden
            }

            wait(&status);                   // auf Kindprozess warten (blockierend)

            // Auswertung: Exit oder Signal?
            if (WIFEXITED(status))
                printf("Child exits with status    %d\n", WEXITSTATUS(status));
            if (WIFSIGNALED(status)) {
                printf("Child exits on signal      %d\n", WTERMSIG(status));
                printf("Child exits with core dump %d\n", WCOREDUMP(status));
            }

        } else {
            // Für Fälle mit längerer Lebensdauer (z. B. sleep in Kind)
            usleep(500 * 1000);  // kurze Pause
            while (!waitpid(pid, &status, WNOHANG)) {
                printf(". . . child is playing\n");  // Kind noch aktiv
                usleep(500 * 1000);  // warte erneut
            }
            printf("Child has exited with 'exit(%d)'\n", WEXITSTATUS(status));
        }
        break;
    }

    exit(0);  // Elternprozess beendet sich
}
