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
// begin students to add code for task 4.1

#include "read.h"
#include <stdio.h>
#include <stdbool.h>

#define ASCII_SPACE 32
#define ASCII_DIGIT_0 48
#define ASCII_DIGIT_9 57
#define BUFFERSIZE 10

int getInt(int maxResult)
{
    unsigned char buffer[BUFFERSIZE] = {0}; // Puffer initialisieren
    int result = 0;
    int bytes = 0;
    int input = getchar();

    // Lese die gesamte Eingabezeile
    while (input != '\n' && input != EOF)
    {
        if (bytes < BUFFERSIZE)
        {
            buffer[bytes++] = (unsigned char)input;
        }
        else
        {
            result = PARSE_ERROR; // Pufferüberlauf
        }
        input = getchar();
    }

    if (input == EOF)
    {
        result = READ_ERROR; // EOF-Error
    }

    int pos = 0;
    while (pos < bytes && buffer[pos] <= ASCII_SPACE)
        pos++;
    int posOfFirstDigit = pos;
    int posOfLastDigit = -1;

    while (pos < bytes && buffer[pos] >= ASCII_DIGIT_0 && buffer[pos] <= ASCII_DIGIT_9)
    {
        posOfLastDigit = pos;
        pos++;
    }

    while (pos < bytes && buffer[pos] <= ASCII_SPACE)
        pos++;

    if (result != 0)
    {
        // Bereits ein Fehler erkannt
    }
    else if (pos != bytes || posOfLastDigit == -1)
    {
        result = PARSE_ERROR;
    }
    else
    {
        for (int i = posOfFirstDigit; i <= posOfLastDigit; i++)
        {
            result = result * 10 + (buffer[i] - ASCII_DIGIT_0);
            if (result > maxResult)
            {
                result = PARSE_ERROR;
                break;
            }
        }
    }

    return result;
}

// end students to add code
