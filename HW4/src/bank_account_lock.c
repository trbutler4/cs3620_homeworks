#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "benchmark.h"

typedef struct account {
    unsigned int account;
    int balance;
    struct account *next;
    pthread_mutex_t lock;
} account_t;

typedef struct ledger {
    account_t *head;
    account_t *tail;
    pthread_rwlock_t lock;
} ledger_t;

int create_account(unsigned int account, ledger_t *l) {
    pthread_rwlock_wrlock(&l->lock); // get the write lock
    account_t *curAcc = l->head;
    while (curAcc != NULL){
        if (curAcc->account == account){
            pthread_rwlock_unlock(&l->lock);
            return -1;
        }
        curAcc = curAcc->next;
    }
    
    account_t *newAcc = (account_t*) malloc(sizeof(ledger_t));
    pthread_mutex_init(&newAcc->lock, NULL);
    newAcc->account = account;
    newAcc->balance = 0;
    newAcc->next = NULL;

    if (l->head == NULL){
        l->head = newAcc;
        l->tail = newAcc;
    }
    else{
        newAcc->next = l->head;
        l->head = newAcc;
    }
    pthread_rwlock_unlock(&l->lock);

    return account;
}

void list_accounts(void *ledger) {

    ledger_t *t = (ledger_t*) ledger;

    pthread_rwlock_rdlock(&t->lock);
    account_t *curAcc = t->head;

    while (curAcc != NULL){
        printf("%d %d\n", curAcc->account, curAcc->balance);
        curAcc = curAcc->next;
    }
    pthread_rwlock_unlock(&t->lock);
}

int modify_balance(unsigned int account, int amount, ledger_t *l) {
    account_t *curAcc = l->head;

    // check for account
    pthread_rwlock_rdlock(&l->lock); // get the read lock
    while (curAcc != NULL){
        if (curAcc->account == account){
            pthread_mutex_lock(&curAcc->lock);
            curAcc->balance += amount;
            pthread_mutex_unlock(&curAcc->lock);
        }
        curAcc = curAcc->next;
    }
    pthread_rwlock_unlock(&l->lock);
    return -1;
}



int main() {
    ledger_t ledger;
    ledger.head = NULL;
    ledger.tail = NULL;
    pthread_rwlock_init(&ledger.lock, NULL);


    double time_taken;
    int accounts = 100;
    printf("accounts: %d\n", accounts);
    time_taken = benchmark_driver(1, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    time_taken = benchmark_driver(10, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    time_taken = benchmark_driver(100, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    time_taken = benchmark_driver(1000, 10000, accounts, &ledger);
    printf("%f\n", time_taken);

    return 0;
}
