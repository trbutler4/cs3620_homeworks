#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // get number from user
    char *input = argv[1];
    int N = atoi(input);

    int n1 = 0;
    int n2 = 1;
    int n3;

    // print first two numbers
    printf("\n%d", n1);
    printf("\n%d", n2);
    
    for (int i = 0; i <= N-2; i++){
        n3 = n1 + n2;
        printf("\n%d", n3);
        n1 = n2;
        n2 = n3;    
    }
    printf("\n");

    return 0;
}

