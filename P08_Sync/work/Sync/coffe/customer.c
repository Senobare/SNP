/*******************************************************************************
* File:     customer.c
* Purpose:  customer thread
* Course:   bsy
* Author:   M. Thaler, 2011
* Revision: 5/2012
* Version:  v.fs20
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>

#include "commonDefs.h"
#include "mrand.h"

#include "commonDefs.h"  // Contains NUM_COINS definition

//*****************************************************************************

void *customer(void* data) {
    /**
    float  ranNum;
    int    i;
    rand_t randnum;

    cData *cD = (cData *) data;

    rand_seed(&randnum, 0); 

    // put coin and select coffee
     for (i = 0; i < ITERATIONS/CUSTOMERS; i++) {
        ranNum = rand_float(&randnum);
        
        pthread_mutex_lock(&(cD->lock));
        cD->coinCount += 1;
        if (ranNum < 0.5) cD->selCount1 += 1;
        else cD->selCount2 += 1;
        pthread_mutex_unlock(&(cD->lock));
    }
    
    pthread_exit(0);  
    **/

    cData *cD = (cData *)data;
    rand_t randnum;
    rand_seed(&randnum, 0);

    for (int i = 0; i < ITERATIONS/CUSTOMERS; i++) {
        // Wait for machine ready
        sem_wait(&(cD->semCoffeeReady));

        // Insert coins
        for (int j = 0; j < NUM_COINS; j++) {
            pthread_mutex_lock(&(cD->lock));
            cD->coinCount++;
            pthread_mutex_unlock(&(cD->lock));
            
            (void) printf("Customer %ld: Inserting coin %d\n", pthread_self(), j+1);
            sem_post(&(cD->semCoinInserted));
            usleep(100000); // Simulate coin insertion delay
        }

        // Select coffee
        pthread_mutex_lock(&(cD->lock));
        if (rand_float(&randnum) < 0.5) cD->selCount1++;
        else cD->selCount2++;
        pthread_mutex_unlock(&(cD->lock));
    }
    pthread_exit(0);
}

//*****************************************************************************
