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

#include "rectang.h"
#include <stdbool.h>

bool Rectangular(int a, int b, int c)
{
    int aS = a * a;
    int bS = b * b;
    int cS = c * c;

    if ((a == 0) && (b == 0) && (c == 0))
    {
        return false;
    }
    else if ((aS + bS) == cS)
    {
        return true;
    }
    else if ((aS + cS) == bS)
    {
        return true;
    }
    else if ((bS + cS) == aS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// end students to add code
