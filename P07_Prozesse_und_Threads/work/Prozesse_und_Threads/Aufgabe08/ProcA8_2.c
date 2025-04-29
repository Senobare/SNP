//***************************************************************************
// File:             ProcA8_2.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Demonstration der Auswirkungen von fork() auf
//                   globale Variablen und unabhängige Speicherbereiche
//                   nach einem Fork. Eltern- und Kindprozess manipulieren
//                   jeweils eine Hälfte eines Arrays und zeigen dann
//                   ihren eigenen Zustand an.
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>   // Datentypen wie pid_t
#include <sys/wait.h>    // wait(), Warten auf Kindprozesse
#include <sys/time.h>    // gettimeofday(), für zufällige Steuerung
#include <unistd.h>      // fork(), usleep()
#include <stdio.h>       // printf(), perror(), fflush()
#include <errno.h>       // Fehlernummern
#include <stdlib.h>      // exit(), random(), srandom()

//***************************************************************************
// Definitionen
//***************************************************************************

#define WAIT_TIME (200*1000)        // Wartezeit in Mikrosekunden (0,2 Sekunden)
#define ARRAY_SIZE 8                // Größe des globalen Arrays (8x8)

// Globaler Array
char GArray[ARRAY_SIZE][ARRAY_SIZE];  // 8x8 Array aus Zeichen

//***************************************************************************
// Funktion: main()
// Parameter: keine
//***************************************************************************

int main(void) {

    pid_t  pid;     // Prozess-ID für Kind
    int    i, j;    // Schleifenvariablen

    // --- Zufällige Entscheidung, wer zuerst schreiben darf
    struct timeval tv;
    gettimeofday(&tv, NULL);    // aktuelle Zeit abrufen
    srandom(tv.tv_usec);        // Zufallszahlengenerator initialisieren
    int head = (int)(random()) >> 7;  // eine Zufallszahl erzeugen
    head &= 0x1;                // nur das niederwertigste Bit verwenden (0 oder 1)

    // --- Globales Array initialisieren und ausgeben
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++) {
            GArray[i][j] = '-';    // Alle Felder mit '-' füllen
            printf("%c ", GArray[i][j]);
        }
        printf("\n");
    }
    fflush(stdout);    // Alle bisher gepufferten Ausgaben sofort ausgeben

    // --- fork()-Aufruf: Kindprozess erzeugen
    pid = fork();

    switch (pid) {
      case -1:  // Fehler beim Fork
            perror("Could not fork");
            break;

      case 0:   // --- Kindprozess
            if (head) usleep(WAIT_TIME);  // Verzögerung einbauen, falls Elternprozess zuerst schreiben soll
            // Kindprozess beschreibt die untere Hälfte des Arrays mit 'c'
            for (i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++)
                for (j = 0; j < ARRAY_SIZE; j++)
                    GArray[i][j] = 'c';
            break;

      default:  // --- Elternprozess
            if (!head) usleep(WAIT_TIME);  // Verzögerung einbauen, falls Kindprozess zuerst schreiben soll
            // Elternprozess beschreibt die obere Hälfte des Arrays mit 'p'
            for (i = 0; i < ARRAY_SIZE / 2; i++)
                for (j = 0; j < ARRAY_SIZE; j++)
                    GArray[i][j] = 'p';
            break;
    }

    // --- Ausgabe: Wer zeigt welches Array?
    if (pid == 0)
        printf("\nKinderarray\n\n");
    else
        printf("\nElternarray\n\n");

    // --- Array ausgeben
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++)
            printf("%c ", GArray[i][j]);
        printf("\n");
    }
    fflush(stdout);  // Ausgabe abschließen

    if (pid > 0) wait(NULL);  // Elternprozess wartet auf Kind

    exit(0);  // Programmende
}

//***************************************************************************
