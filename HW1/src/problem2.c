#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    // get number from user
    char *input = argv[1];
    int N = atoi(input);
    printf("\n%d", N);

    int isPrime;

    for (int i = 1; i < N; i++){
        isPrime = 1;
        for (int j = 2; j < i; j++){
            if (i % j == 0){
                // not a prime number 
                isPrime = 0;
            }
        }
        if (isPrime == 1){
            printf("\n%d", i);
        }
    }
    printf("\n");

    return 0;

}