/******************************************************************************
* File:            Daemonizer.c
* Original Autor:  M. Thaler (Modul BSY)
* Aufgabe:         Einen Daemon-Prozess erzeugen
*
* Beschreibung:
* Diese Datei enthält die zentrale Funktion `Daemonizer()`, mit der ein
* Prozess sich korrekt in einen Daemon umwandelt:
* - Abtrennung vom Terminal (double-fork, setsid, signal handling)
* - Erstellung eines Lockfiles zur Vermeidung von Mehrfachstarts
* - Umleitung von stdout/stderr auf eine Logdatei (optional)
******************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

//*****************************************************************************
// Hilfsmakro für Debug-Zwecke (derzeit deaktiviert)
#define OutPutPIDs() printf("\nPID %d, PPID %d, GRP-ID %d\n", getpid(), getppid(), getpgrp())
//*****************************************************************************

//*****************************************************************************
// Funktion:    lock()
// Aufgabe:     Sperrt eine Datei exklusiv über fcntl() (schreibend)
// Parameter:   fd – Datei-Deskriptor des Lockfiles
// Rückgabe:    0 bei Erfolg, -1 wenn Datei bereits gesperrt (Daemon läuft)
//              Bei fatalen Fehlern: Programmabbruch
//*****************************************************************************
int lock(int fd) {
    int retval, len;
    struct flock lock;
    char buffer[16];

    // Lockstruktur konfigurieren: schreibender Lock über gesamte Datei
    lock.l_type   = F_WRLCK;
    lock.l_start  = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len    = 0;

    retval = fcntl(fd, F_SETLK, &lock);
    if (retval < 0) {
        if ((errno == EACCES) || (errno == EAGAIN)) {
            return -1; // Datei ist bereits gesperrt → Daemon läuft
        } else {
            perror("fatal error when locking file");
            exit(-1);
        }
    }

    // Lockfile leeren
    if (ftruncate(fd, 0) < 0) {
        perror("fatal error when emptying lockfile");
        exit(-1);
    }

    // PID in Lockfile schreiben
    sprintf(buffer, "%d\n", getpid());
    len = strlen(buffer);
    if (write(fd, buffer, len) < len) {
        perror("fatal error when writing pid to lockfile");
        exit(-1);
    }

    // Lockfile beim exec automatisch schließen
    retval = fcntl(fd, F_GETFD, 0);
    if (retval < 0) {
        perror("fatal error when reading lockfile flags");
        exit(-1);
    }
    retval |= FD_CLOEXEC;
    if (fcntl(fd, F_SETFD, retval) < 0) {
        perror("fatal error when setting lockfile flags");
        exit(-1);
    }

    return 0;
}

//*****************************************************************************
// Funktion:    Daemonizer()
// Aufgabe:     Wandelt den aktuellen Prozess in einen Daemon um und
//              startet die übergebene Daemon-Funktion
//
// Parameter:
//   - Daemon(): Funktionszeiger auf die Hauptfunktion des Daemons
//   - data: beliebige Nutzdaten (üblicherweise Konfiguration oder Name)
//   - LockFile: Pfad zur Lockdatei zur Mehrfachstartvermeidung (NULL = keine)
//   - LogFile: Pfad zur Logdatei (NULL = keine Ausgabeumleitung)
//   - LivDir: Arbeitsverzeichnis des Daemons
//
// Rückgabe:    Sollte nie zurückkehren (außer bei Fehlern)
//*****************************************************************************
int Daemonizer(void Daemon(void *), void *data,
               const char *LockFile, const char *LogFile, const char *LivDir) {

    pid_t PID;
    int fd, dummyfd, retval;

    OutPutPIDs();  // optionaler Debug-Ausdruck

    // ========== 1. fork() zum Abtrennen vom Elternprozess ==========
    PID = fork();
    if (PID < 0) {
        perror("could not fork()");
        exit(-1);
    } else if (PID > 0) {
        exit(0);  // Elternprozess beendet sich sofort
    }

    // ========== 2. Kindprozess: eigentlicher Daemon ==========
    // Signale ignorieren, da Terminalbindung entfällt
    signal(SIGINT,  SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGHUP,  SIG_IGN);

    setsid();           // Neue Session + Gruppenführer → vollständige Trennung vom Terminal
    chdir(LivDir);      // Wechsle ins Arbeitsverzeichnis
    umask(0);           // Dateiberechtigungen nicht einschränken

    // ========== 3. Lockfile prüfen ==========
    if (LockFile != NULL) {
        fd = open(LockFile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd < 0) {
            perror("fatal error when opening lockfile");
            exit(-1);
        }
        retval = lock(fd);
        if (retval < 0) {
            printf("\n*** daemon is already running ***\n");
            exit(0);  // Normal beenden, kein Fehler
        }
    }

    printf("\n*** daemon starts with process id: %d ***\n", getpid());

    // ========== 4. Umleitung von stdout/stderr auf Logdatei (optional) ==========
    close(1);  // stdout schließen
    close(2);  // stderr schließen

    if (LogFile != NULL) {
        enum {UserWrite = 0644};
        dummyfd = open(LogFile, O_CREAT | O_APPEND | O_WRONLY, UserWrite);
        if (dummyfd < 0) {
            perror("could not open log file");
            exit(-1);
        }
        dup(1);  // stderr wird auf dasselbe wie stdout gesetzt (beide in Logfile)
    }

    close(0);  // stdin schließen

    // ========== 5. Starte die übergebene Daemon-Funktion ==========
    Daemon(data);

    // Sollte nie erreicht werden
    return 0;
}
