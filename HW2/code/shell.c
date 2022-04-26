#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char *argv[]){
    
    // get input from user
    char input[1024];
    while (0 == 0){
        printf("SimpleShell$ ");
        fgets(input, 1024, stdin);

        // quit when user enters "quit"
        if (strcmp(input, "quit\n") == 0)
            break;

        // execute  
        char *ssArgs[1024] = {};
        char *tok  = strtok(input, " ");
        char *prog = tok;
        //printf("%s\n", prog);
        int i = 1;
        ssArgs[0] = prog;
        //tok = strtok(NULL, " ");
        while (tok != NULL){
            tok = strtok(NULL, " ");
            ssArgs[i] = tok;
            //printf("%s\n", ssArgs[i]);
            i++;
        }


        // fork and execute program
        int child = fork();

        if (child == 0){
            //printf("%s\n", prog);
            /*
            for (int i = 0; ssArgs[i] != NULL; i++){
                printf("%s\n", ssArgs[i]);
            }
            */
            execv(prog, ssArgs);
            break;
        } else {
            wait(0);
        }
    
    }

    return 0;

}

