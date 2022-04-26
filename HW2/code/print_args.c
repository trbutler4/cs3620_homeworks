#include <stdio.h>

int main (int argc, char *argv[]){

    printf("%d arguments read", argc-1);    

    for (int i = 1; i < argc; i++){
        printf("\n%s", argv[i]);
    }
    printf("\n"); 
    
    return 0;

}
