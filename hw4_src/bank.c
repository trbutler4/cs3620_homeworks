#include <stdio.h>
#include <stdlib.h>
#include "bank_interface.h"

typedef struct account {
    unsigned int account;
    int balance;
    struct account *next;
} account_t;

typedef struct ledger {
    account_t *head;
    account_t *tail;
} ledger_t;

int create_account(unsigned int account, void *ledger) {
    ledger_t *t = (ledger_t*) ledger;
    account_t *curAcc = t->head;

    while (curAcc != NULL){
        if (curAcc->account == account){
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
    
    return account;
}

void list_accounts(void *ledger) {
    ledger_t *t = (ledger_t*) ledger;
    account_t *curAcc = t->head;
    while (curAcc != NULL){
        printf("%d %d\n", curAcc->account, curAcc->balance);
        curAcc = curAcc->next;
    }
}

int modify_balance(unsigned int account, int amount, void *ledger) {
    ledger_t *t = (ledger_t*) ledger;
    account_t *curAcc = t->head;

    // check for account
    while (curAcc != NULL){
        if (curAcc->account == account){
            curAcc->balance += amount;
        }
        curAcc = curAcc->next;
    }
    return -1;
}

int main() {
    ledger_t ledger;
    ledger.head = NULL;
    ledger.tail = NULL;

    create_account(0, &ledger);
    create_account(1, &ledger);
    create_account(2, &ledger);

    list_accounts(&ledger);
    
    modify_balance(1, 10, &ledger);
    modify_balance(0, -100, &ledger);
    modify_balance(123, -100, &ledger);

    list_accounts(&ledger);

    return 0;
}
