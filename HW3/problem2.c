#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    fork();
    fork();

    printf("%d\n", getpid());

    exit(0);
}