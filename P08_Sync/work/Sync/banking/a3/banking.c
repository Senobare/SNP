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

typedef struct account_struct_
{
    long int balance;
    pthread_mutex_t acntLock;
} Account;

typedef struct branch_struct
{
    Account *accounts;
    pthread_mutex_t branchLock;
} Branch;

//******************************************************************************

static Branch *bank;
static int nBranches, nAccounts;

//******************************************************************************
// banking functions

void makeBank(int num_branches, int num_accounts)
{
    nBranches = num_branches;
    nAccounts = num_accounts;
    bank = (Branch *)malloc(nBranches * sizeof(Branch));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);

    for (int i = 0; i < nBranches; i++)
    {
        pthread_mutex_init(&bank[i].branchLock, NULL);
        bank[i].accounts = (Account *)malloc(nAccounts * sizeof(Account));
        for (int j = 0; j < nAccounts; j++)
        {
            pthread_mutex_init(&bank[i].accounts[j].acntLock, NULL);
            bank[i].accounts[j].balance = 0;
        }
    }
}

void deletebank(void)
{
    for (int i = 0; i < nBranches; i++)
        free(bank[i].accounts);
    free(bank);
    nBranches = nAccounts = 0;
}

long int withdraw(int branchNr, int accountNr, long int value)
{
    int rv, tmp;
    rv = 0;
    tmp = bank[branchNr].accounts[accountNr].balance - value;
    if (tmp >= 0)
    {
        bank[branchNr].accounts[accountNr].balance = tmp;
        rv = value;
    };
    return rv;
}

void deposit(int branchNr, int accountNr, long int value)
{
    bank[branchNr].accounts[accountNr].balance += value;
}

void transfer(int fromB, int toB, int accountNr, long int value)
{
    if (fromB == toB)
    {
        // Handle transfers within the same branch
        pthread_mutex_lock(&bank[fromB].branchLock);

        // Withdraw and deposit atomically within the branch
        int money = withdraw(fromB, accountNr, value);
        if (money > 0)
        {
            deposit(toB, accountNr, money);
        }

        pthread_mutex_unlock(&bank[fromB].branchLock);
    }
    else
    {
        // Lock branches in consistent order for cross-branch transfers
        int first = (fromB < toB) ? fromB : toB;
        int second = (fromB < toB) ? toB : fromB;

        pthread_mutex_lock(&bank[first].branchLock);
        pthread_mutex_lock(&bank[second].branchLock);

        // Perform transfer
        int money = withdraw(fromB, accountNr, value);
        if (money > 0)
        {
            deposit(toB, accountNr, money);
        }

        // Release locks in reverse order
        pthread_mutex_unlock(&bank[second].branchLock);
        pthread_mutex_unlock(&bank[first].branchLock);
    }
}

void checkAssets(void)
{
    static long assets = 0;
    long int sum = 0;
    for (int i = 0; i < nBranches; i++)
    {
        for (int j = 0; j < nAccounts; j++)
        {
            sum += (long int)bank[i].accounts[j].balance;
        }
    }
    if (assets == 0)
    {
        assets = sum;
        printf("Balance of accounts is: %ld\n", sum);
    }
    else
    {
        if (sum != assets)
        {
            printf("Balance of accounts is: %ld ... not correct\n", sum);
        }
        else
            printf("Balance of accounts is: %ld ... correct\n", assets);
    }
}

// Revised checkIBC function
int checkIBC(void)
{
    static long ibcError = 0;
    long sum = 0;

    // Lock all branches in order
    for (int i = 0; i < nBranches; i++)
    {
        pthread_mutex_lock(&bank[i].branchLock);
    }

    // Sum balances
    for (int i = 0; i < nBranches; i++)
    {
        for (int j = 0; j < nAccounts; j++)
        {
            sum += bank[i].accounts[j].balance;
        }
    }

    // Unlock in reverse order
    for (int i = nBranches - 1; i >= 0; i--)
    {
        pthread_mutex_unlock(&bank[i].branchLock);
    }

    if (ibcError == 0)
        ibcError = sum;
    return (ibcError != sum);
}
//******************************************************************************

/**
Why do implementations from 5.2 and 5.3 NOT satisfy the IBC requirements?

5.2 (account-level locking):
Locks only individual accounts during withdrawal/deposit, so no global coordination across branches.
While accounts are safe individually, the total sum over all branches may be temporarily inconsistent during concurrent transfers between branches,
because transfers lock accounts independently and do not prevent inter-branch race conditions.

5.3 (branch-level locking):
Locks only individual branches, but transfer involves two branches, and locks are acquired separately.
This can cause race conditions and inconsistent total balance when concurrent transfers between branches overlap without global locking.

In both cases, there is no locking scheme guaranteeing that the sum of all account balances over all branches remains consistent at all times, as required by IBC.

Which locks to use to satisfy IBC?

The IBC requires global consistency: total assets must always be consistent across all branches.
You cannot introduce new locks — so you must use existing branchLock and acntLock.
You need to lock all branches and accounts involved in the transfer, or even better all branches/accounts, before proceeding to guarantee total consistency.
But locking all branches and all accounts simultaneously is expensive and may reduce concurrency.

*/