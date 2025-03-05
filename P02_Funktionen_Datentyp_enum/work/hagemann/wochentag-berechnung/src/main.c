 /* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur             -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences)           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 */
/**
 * @file
 * @brief Lab P02 weekday
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// *** TASK1: typedef enum types for month_t (Jan=1,...Dec} ***
// BEGIN-STUDENTS-TO-ADD-CODE

typedef enum {
    Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
} month_t;

// END-STUDENTS-TO-ADD-CODE



// *** TASK1: typedef struct for date_t ***
// BEGIN-STUDENTS-TO-ADD-CODE

typedef struct {
    int year;
    month_t month;
    int day;
} date_t;

// END-STUDENTS-TO-ADD-CODE



// *** TASK2: typedef enum weekday_t (Sun=0, Mon, ...Sat) ***
// BEGIN-STUDENTS-TO-ADD-CODE

typedef enum {
    Sun = 0, Mon, Tue, Wed, Thu, Fri, Sat
} weekday_t;

// END-STUDENTS-TO-ADD-CODE

/**
 * @brief   TASK1: Checks if the given date is a leap year.
 * @returns 0 = is not leap year, 1 = is leap year
 */
// BEGIN-STUDENTS-TO-ADD-CODE

int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;  // Schaltjahr
    }
    return 0;  // Kein Schaltjahr
}

// END-STUDENTS-TO-ADD-CODE


/**
 * @brief   TASK1: Calculates the length of the month given by the data parameter
 * @returns 28, 29, 30, 31 if a valid month, else 0
 */
// BEGIN-STUDENTS-TO-ADD-CODE

int getMonthLength(date_t date) {
    switch (date.month) {
        case Jan: case Mar: case May: case Jul: case Aug: case Oct: case Dec:
            return 31; // Monate mit 31 Tagen
        case Apr: case Jun: case Sep: case Nov:
            return 30; // Monate mit 30 Tagen
        case Feb:
            return isLeapYear(date.year) ? 29 : 28; // Februar (Schaltjahr beachten)
        default:
            return 0; // Ungültiger Monat
    }
}

// END-STUDENTS-TO-ADD-CODE

/**
 * @brief   TASK1: Checks if the given date is in the gregorian date range
 * @returns 0 = no, 1 = yes
 */
// BEGIN-STUDENTS-TO-ADD-CODE

int isGregorianDate(date_t date) {
    return (date.year >= 1582 && date.year <= 9999); // Gültiger gregorianischer Bereich
}

// END-STUDENTS-TO-ADD-CODE


/**
 * @brief   TASK1: Checks if the given date is a valid date.
 * @returns 0 = is not valid date, 1 = is valid date
 */
// BEGIN-STUDENTS-TO-ADD-CODE

int isValidDate(date_t date) {
    return isGregorianDate(date) && date.month >= Jan && date.month <= Dec && 
           date.day >= 1 && date.day <= getMonthLength(date);
}

// END-STUDENTS-TO-ADD-CODE


/**
 * @brief   TASK2: calculated from a valid date the weekday
 * @returns returns a weekday in the range Sun...Sat
 */
// BEGIN-STUDENTS-TO-ADD-CODE

weekday_t calculateWeekday(date_t date) {
    int m = (date.month + 9) % 12 + 1; // Korrigiert Monat
    int a = (date.month < 3) ? date.year - 1 : date.year; // Gleiches für Jahr
    int y = a % 100;  // Beiden Endziffern des Jahres
    int c = a / 100;  // c = century, erste beiden Ziffern

    // Formel (int arithmetic)
    int weekday = (date.day + (13 * m - 1) / 5 + y + y / 4 + c / 4 - 2 * c) % 7;

    // Korrektur für Sunday = 0, Monday = 1, ..., Saturday = 6
    return (weekday + 7) % 7;
}

// END-STUDENTS-TO-ADD-CODE



/**
 * @brief   TASK2: print weekday as 3-letter abreviated English day name
 */
// BEGIN-STUDENTS-TO-ADD-CODE

void printWeekday(weekday_t day) {
    const char *weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    if (day >= Sun && day <= Sat) {
        printf("%s", weekdays[day]);
    } else {
        assert(!"day is out-of-range");
    }
}

// END-STUDENTS-TO-ADD-CODE

/**
 * @brief   main function
 * @param   argc [in] number of entries in argv
 * @param   argv [in] program name plus command line arguments
 * @returns returns success if valid date is given, failure otherwise
 */
int main(int argc, const char *argv[])
{
    // TASK1: parse the mandatory argument into a date_t variable and check if the date is valid
    // BEGIN-STUDENTS-TO-ADD-CODE

    if (argc != 2) {
        fprintf(stderr, "Usage: %s YYYY-MM-DD\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Datum einlesen
    date_t date;
    if (sscanf(argv[1], "%d-%d-%d", &date.year, (int*)&date.month, &date.day) != 3) {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }

    // Überprüfen, ob das Datum gültig ist
    if (!isValidDate(date)) {
        fprintf(stderr, "Invalid date\n");
        return EXIT_FAILURE;
    }

    // END-STUDENTS-TO-ADD-CODE


    // TASK2: calculate the weekday and print it in this format: "%04d-%02d-%02d is a %s\n"
    // BEGIN-STUDENTS-TO-ADD-CODE

    // Wochentag berechnen
    weekday_t weekday = calculateWeekday(date);

    // Ausgabe des Wochentags
    printf("%04d-%02d-%02d is a ", date.year, date.month, date.day);
    printWeekday(weekday);
    printf("\n");

    // END-STUDENTS-TO-ADD-CODE

    return EXIT_SUCCESS;
}

