//******************************************************************************
// Course:  BSy
// File:    banking.c
// Author:  M. Thaler, ZHAW
// Purpose: locking mechanisms
// Version: v.fs20
//******************************************************************************

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "banking.h"

//******************************************************************************

typedef struct account_struct_ {
    long int balance;
    pthread_mutex_t acntLock;
} Account;

typedef struct branch_struct {
    Account *accounts;
    pthread_mutex_t branchLock; 
} Branch;

//******************************************************************************

static Branch *Bank;
static int nBranches, nAccounts;

//******************************************************************************
// banking functions

void makeBank(int num_branches, int num_accounts) {
    nBranches = num_branches;
    nAccounts = num_accounts;
    Bank = (Branch *)malloc(nBranches * sizeof(Branch));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

    for (int  i = 0; i < nBranches; i++) {
        Bank[i].accounts = (Account *)malloc(nAccounts * sizeof(Account));
        pthread_mutex_init(&(Bank[i].branchLock), &attr);
        for (int j = 0; j < nAccounts; j++) {
            Bank[i].accounts[j].balance = 0;
            pthread_mutex_init((&(Bank[i].accounts[j].acntLock)), &attr);
        }
    }
}

void deleteBank(void) {
    for (int i = 0; i < nBranches; i++)
        free(Bank[i].accounts);
    free(Bank);
    nBranches = nAccounts = 0;
}

long int withdraw(int branchNr, int accountNr, long int value) {
    Branch *br = &Bank[branchNr];
    pthread_mutex_lock(&br->branchLock);

    long int rv = 0;
    if (br->accounts[accountNr].balance >= value) {
        br->accounts[accountNr].balance -= value;
        rv = value;
    }

    pthread_mutex_unlock(&br->branchLock);
    return rv;
}

void deposit(int branchNr, int accountNr, long int value) {
    Branch *br = &Bank[branchNr];
    pthread_mutex_lock(&br->branchLock);

    br->accounts[accountNr].balance += value;

    pthread_mutex_unlock(&br->branchLock);
}

void transfer(int fromB, int toB, int accountNr, long int value) {
    int money = withdraw(fromB, accountNr, value);
    if (money >= 0)
        deposit(toB, accountNr, money);
}

void checkAssets(void) {
    static long assets = 0;
    long sum = 0;
    for (int i = 0; i < nBranches; i++) {
        for (int j = 0; j < nAccounts; j++) {
            sum += (long)Bank[i].accounts[j].balance;
        }
    }
    if (assets == 0) {
        assets = sum;
        printf("Balance of accounts is: %ld\n", sum);
    }
    else {
        if (sum != assets)
            printf("Balance of accounts is: %ld ... not correct\n", sum);
        else
            printf("Balance of accounts is: %ld ... correct\n", assets);
    }
}

//******************************************************************************

/**
What do you observe compared to the results from task 5.2? What do you recommend to your supervisor?

Compared to task 5.2, where account-level locking was used (acntLock),
the implementation in task 5.3 with branch-level locking (branchLock) leads to slightly longer execution times,
especially when multiple threads are active. This is because the coarser branch-level lock reduces concurrency: 
operations on different accounts within the same branch can no longer be executed in parallel.
However, the implementation is still correct (no balance mismatches), and the code is simpler and easier to maintain.

Recommendation: If performance is critical and the system must handle high transaction throughput,
I would recommend using fine-grained locking (as in task 5.2). If simplicity, maintainability, or low expected concurrency is more important,
then branch-level locking (as in task 5.3) is acceptable.



A colleague suggests locking the account first and then the branch when withdrawing, but the opposite order when depositing. How do you respond?

This approach is strongly discouraged, as it introduces the risk of deadlocks. If one thread locks an account and waits for the branch lock,
while another thread locks the branch and waits for the account, neither thread can proceed. This circular wait condition is one of the classic causes of deadlock.
To avoid this, all threads must acquire locks in a consistent, global order. Mixing the lock order between withdraw and deposit violates this principle.

 */
