/*******************************************************************************
 * File:     coffeTeller.c
 * Purpose:  coffe teller with pthreads
 * Course:   bsy
 * Author:   M. Thaler, 2011
 * Revision: 5/2012
 * Version:  v.fs20
 *******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <pthread.h>

#include "commonDefs.h"

//******************************************************************************

void *coffeeTeller(void *data)
{

    /**
    int i;
    cData *cD = (cData *)data;

    // now start selling coffee
    (void) printf("\nCoffee teller machine starting\n\n");

    i = 0;
    while (i < ITERATIONS)
    {
        // Only check every 1000 iterations to reduce lock contention
        if (i % 1000 == 0)
        {
            pthread_mutex_lock(&(cD->lock)); // Acquire lock before checking

            if (cD->coinCount != cD->selCount1 + cD->selCount2)
            {
                (void) printf("error c = %5d  s1 =%6d   s2 =%6d   diff: %4d\ti = %d\n",
                       cD->coinCount, cD->selCount1, cD->selCount2,
                       cD->coinCount - cD->selCount1 - cD->selCount2,
                       i);
                cD->coinCount = 0;
                cD->selCount1 = cD->selCount2 = 0;
            }
            pthread_mutex_unlock(&(cD->lock)); // Release lock
        }

        if (i % 1000000 == 0)
            (void) printf("working %d\n", i);
        i++;
    }
    pthread_exit(0);
    **/

    cData *cD = (cData *)data;
    (void) printf("Coffee teller: Startup (requires %d coins per coffee)\n", NUM_COINS);

    for (int i = 0; i < ITERATIONS; i++) {
        // Wait for coins
        for (int j = 0; j < NUM_COINS; j++) {
            if (sem_wait(&(cD->semCoinInserted)) != 0) {
                perror("sem_wait failed");
                pthread_exit(NULL);
            }
            (void) printf("Teller: Received coin %d/%d\n", j+1, NUM_COINS);
        }

        // Dispense coffee
        (void) printf("Teller: Dispensing coffee\n");
        if (sem_post(&(cD->semCoffeeReady)) != 0) {
            perror("sem_post failed");
        }

        // Progress indicator
        if (i % 1000 == 0) (void) printf("Completed %d orders\n", i);
    }
    
    (void) printf("Teller: Completed %d iterations\n", ITERATIONS);
    pthread_exit(0);
}

//******************************************************************************
