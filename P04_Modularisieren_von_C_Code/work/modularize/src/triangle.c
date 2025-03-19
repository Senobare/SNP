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
 * @brief Lab implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "rectang.h"

/// max side length
#define MAX_NUMBER 1000

/**
 * @brief Main entry point.
 * @returns Returns EXIT_SUCCESS (=0) on success, EXIT_FAILURE (=1) on failure.
 */
int main(void)
{
	// begin students to add code for task 4.1

	while (1)
	{
		printf("\nDreiecksbestimmung (CTRL-C: Abbruch)\n\n");

		int word = 0;
		int a = 0, b = 0, c = 0;

		// Eingabe für a
		do
		{
			printf("Seite a: ");
			word = getInt(MAX_NUMBER);
		} while (word == PARSE_ERROR); // Wiederhole bei Parse-Fehler

		if (word == READ_ERROR)
		{
			printf("\n\nbye bye\n\n"); // Zwei Zeilenumbrüche vor und nach "bye bye"
			break;
		}
		a = word;

		// Eingabe für b (analog zu a)
		do
		{
			printf("Seite b: ");
			word = getInt(MAX_NUMBER);
		} while (word == PARSE_ERROR);

		if (word == READ_ERROR)
		{
			printf("\n\nbye bye\n\n"); // Zwei Zeilenumbrüche vor und nach "bye bye"
			break;
		}
		b = word;

		// Eingabe für c (analog zu a)
		do
		{
			printf("Seite c: ");
			word = getInt(MAX_NUMBER);
		} while (word == PARSE_ERROR);

		if (word == READ_ERROR)
		{
			printf("\n\nbye bye\n\n"); // Zwei Zeilenumbrüche vor und nach "bye bye"
			break;
		}
		c = word;

		// Verarbeitung und Ausgabe des Ergebnisses
		if (Rectangular(a, b, c))
		{
			printf("-> Dreieck %d-%d-%d ist rechtwinklig\n\n\n", a, b, c); // Drei Leerzeilen
		}
		else
		{
			printf("-> Dreieck %d-%d-%d ist nicht rechtwinklig\n\n\n", a, b, c); // Drei Leerzeilen
		}
	}

	// end students to add code
	return EXIT_SUCCESS;
}
