//***************************************************************************
// File:             ProcA9.c
// Original Author:  M. Thaler (Modul BSY)
// Beschreibung:     Demonstriert paralleles Arbeiten mit zwei Threads auf
//                   einem gemeinsamen globalen Array. Jeder Thread
//                   beschreibt eine Hälfte des Arrays mit unterschiedlichen
//                   Buchstaben ('p' oder 'c').
//***************************************************************************

//***************************************************************************
// System-Includes
//***************************************************************************

#include <sys/types.h>    // Datentypen wie pid_t
#include <sys/wait.h>     // Warten auf Prozesse (hier nicht genutzt, nur traditionell inkludiert)
#include <sys/time.h>     // gettimeofday() für Zufallssteuerung
#include <unistd.h>       // Standardfunktionen wie sleep(), usleep()
#include <stdio.h>        // printf(), perror()
#include <errno.h>        // Fehlerbehandlung
#include <stdlib.h>       // exit(), srandom(), random()
#include <pthread.h>      // Threads mit pthreads

// Lokales Modul
#include "selectCPU.h"    // CPU-Bindung auf CPU 0

//***************************************************************************
// Globale Daten
//***************************************************************************

#define ARRAY_SIZE 8
char GArray[ARRAY_SIZE][ARRAY_SIZE];    // Globales 8x8-Array

//***************************************************************************
// Thread-Funktion: ThreadF
// Parameter: void *letter – zeigt auf den Buchstaben, den der Thread schreiben soll
//***************************************************************************

void *ThreadF(void *letter) {
    int    i, j;
    int    LowLim, HighLim;
    char   letr;

    letr = *(char *)letter;  // Dereferenzieren des Parameters (Buchstabe)

    if (letr == 'p') {        // Wenn Buchstabe 'p', bearbeite untere Hälfte
        LowLim = 0;
        HighLim = ARRAY_SIZE / 2;
    } else {                  // Sonst obere Hälfte
        LowLim = ARRAY_SIZE / 2;
        HighLim = ARRAY_SIZE;
    }

    // Fülle die eigene Hälfte des Arrays
    for (i = LowLim; i < HighLim; i++) {
        for (j = 0; j < ARRAY_SIZE; j++)
            GArray[i][j] = letr;
    }

    // Gib das gesamte Array aus (aktueller Zustand)
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++)
            printf("%c ", GArray[i][j]);
        printf("\n");
    }
    printf("\n");

    fflush(stdout);     // Terminalausgabe sofort schreiben
    while (1) { }   // Endlosschleife
    pthread_exit(0);    // Thread sauber beenden
}

//***************************************************************************
// Funktion: main()
// Parameter: keine
//***************************************************************************

int main(void) {

    pthread_t thread1, thread2;  // Zwei Thread-IDs
    int       i, j, pthr;
    char      letter1, letter2;

    selectCPU(0);  // Setze CPU-Affinität auf CPU 0 (damit beide Threads auf derselben CPU laufen)

    // Zufällige Entscheidung: welcher Buchstabe startet zuerst
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srandom(tv.tv_usec);
    int head = (int)(random()) >> 7;
    head &= 0x1;
    if (head) {
        letter1 = 'p';
        letter2 = 'c';
    } else {
        letter1 = 'c';
        letter2 = 'p';
    }

    // Array initialisieren mit '-'
    for (i = 0; i < ARRAY_SIZE; i++)
        for (j = 0; j < ARRAY_SIZE; j++)
            GArray[i][j] = '-';

    printf("\nArray vor Threads\n\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++)
            printf("%c ", GArray[i][j]);
        printf("\n");
    }
    printf("\n");

    // Threads erzeugen
    pthr = pthread_create(&thread1, NULL, ThreadF, (void *)&letter1);
    if (pthr != 0) perror("Could not create thread");

    pthr = pthread_create(&thread2, NULL, ThreadF, (void *)&letter2);
    if (pthr != 0) perror("Could not create thread");

    // Auf die Beendigung beider Threads warten
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Endzustand des Arrays ausgeben
    printf("\n... nach Threads\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++)
            printf("%c ", GArray[i][j]);
        printf("\n");
    }
}

//***************************************************************************
