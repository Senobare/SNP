/**
 *  P02 Praktikum
 *
 *  Das Programm liest einen Monat (1-12) und ein Jahr (1600-2400) ein und
 *  gibt die Anzahl der Tage dieses Monats aus.
 *
 *  @author Gerrit Burkert, Adaptation bazz
 *  @version 15-FEB-2013, 16-OCT-2017, 17-OCT-2019, 16-FEB-2022
 */

#include <stdio.h>
#include <stdlib.h>

#define ERROR_IN_MONTH 1
#define ERROR_IN_YEAR 2

#define TRUE 1
#define FALSE 0

///// Student Code

// Funktion zum Einlesen und Überprüfen eines Ganzzahlwertes im angegebenen Bereich
int gibIntWert(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s (%d - %d): ", prompt, min, max);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
          // fgets() sicherer Weg anstatt scnaf
            break;
        }
        printf("Ungültige Eingabe. Bitte wiederholen.\n");
    }
    return value;
}

// Funktion, um zu prüfen, ob ein Jahr ein Schaltjahr ist
int istSchaltjahr(int jahr) {
    if ((jahr % 4 == 0 && jahr % 100 != 0) || (jahr % 400 == 0)) {
        return TRUE; // Magic numbers ersetzen durch eigene Symbole. Durch Symbole ersetzen, welche lesbar & sinnvoll sind
    }
    return FALSE;
}

// Funktion, um die Anzahl der Tage im angegebenen Monat und Jahr zu berechnen
int tageProMonat(int jahr, int monat) {
    switch (monat) {
        case 1:  // Januar
        case 3:  // März
        case 5:  // Mai
        case 7:  // Juli
        case 8:  // August
        case 10: // Oktober
        case 12: // Dezember
            return 31;
        case 4:  // April
        case 6:  // Juni
        case 9:  // September
        case 11: // November
            return 30;
        case 2:  // Februar
            return istSchaltjahr(jahr) ? 29 : 28;
        default:
            return 0; // Ungültiger Monat
    }
}

///// END Student Code


int main (int argc, char *argv[]) {
    
    int monat, jahr;
     
    //  Monat einlesen und Bereich ueberpruefen
    monat = gibIntWert("Monat", 1, 12);
    jahr  = gibIntWert("Jahr", 1600, 9999);
	
    //  Ausgabe zum Test
    (void) printf("Monat: %d, Jahr: %d \n", monat, jahr);
    
    //  Ausgabe zum Test (hier mit dem ternaeren Operator "?:")
    (void) printf("%d ist %s Schaltjahr\n", jahr, istSchaltjahr(jahr) ? "ein" : "kein");

    // Ausgabe
    (void) printf("Der Monat %02d-%d hat %d Tage.\n", monat, jahr, tageProMonat(jahr, monat));
   
    return 0;
}
