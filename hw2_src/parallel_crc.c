#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// sleep for ~5 seconds 
u_int8_t gencrc(u_int8_t *data, size_t len)
{
    u_int8_t crc = 0xff;
    size_t i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (u_int8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    return crc;
}

int main(int argc, char *argv[]) {
    // read in files
    for (int i = 1; argv[i] != NULL; i++){
	char *arg = argv[i];
	FILE* tmp = fopen(arg, "r");

        // determine size 
        int seek = fseek(tmp, 0L, SEEK_END);
        int size = ftell(tmp);
        //printf("\nseek %d", seek);
        //printf("\nsize %d", size); 

        // malloc create a character array buffer to read into -> data 
        u_int8_t *buf = malloc(size); 

        // create child process 
        int child = fork();

        if (child == 0){
            //printf("child, %d", getpid());
            // generate crc
            u_int8_t crc = gencrc(buf, size);
            printf("\n%s=%d", arg, crc);
            // end the child (break)
            break;
        }else {
            //printf("parent, %d", getpid());
            // wait for child processes to end 
            wait(0);
            
        }
        
    } 
    printf("\n"); 
    return 0;
}
