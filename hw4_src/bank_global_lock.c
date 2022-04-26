#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "bank_interface.h"
#include "benchmark.h"

typedef struct account {
    unsigned int account;
    int balance;
    struct account *next;
} account_t;

typedef struct ledger {
    account_t *head;
    account_t *tail;
    pthread_mutex_t lock;
} ledger_t;

int create_account(unsigned int account, void *ledger) {
    ledger_t *t = (ledger_t*) ledger;
    account_t *curAcc = t->head;
 
    // check for account
    pthread_mutex_lock(&t->lock);
    while (curAcc != NULL){
        if (curAcc->account == account){
            pthread_mutex_unlock(&t->lock);
            return -1;
        }
        curAcc = curAcc->next;
    }

    account_t *newAcc = (account_t*) malloc(sizeof(ledger_t));
    newAcc->account = account;
    newAcc->balance = 0;
    newAcc->next = NULL;

    if (t->head == NULL){
        t->head = newAcc;
        t->tail=newAcc;
    }
    else{
        newAcc->next = t->head;
        t->head = newAcc;
    }
    pthread_mutex_unlock(&t->lock);

    return account;
}

void list_accounts(void *ledger) {
    ledger_t *t = (ledger_t*) ledger;
    account_t *curAcc = t->head;

    pthread_mutex_lock(&t->lock);
    while (curAcc != NULL){
        printf("%d %d\n", curAcc->account, curAcc->balance);
        curAcc = curAcc->next;
    }
    pthread_mutex_unlock(&t->lock);
}

int modify_balance(unsigned int account, int amount, void *ledger) {
    ledger_t *t = (ledger_t*) ledger;
    account_t *curAcc = t->head;

    pthread_mutex_lock(&t->lock);
    while (curAcc != NULL){
        if (curAcc->account == account){
            curAcc->balance += amount;
        }
        curAcc = curAcc->next;
    }
    pthread_mutex_unlock(&t->lock);

    return 0;
}

int main() {
    ledger_t ledger;
    ledger.head = NULL;
    ledger.tail = NULL;
    pthread_mutex_init(&ledger.lock, NULL);
    
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
