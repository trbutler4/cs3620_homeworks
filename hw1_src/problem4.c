#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    // get file names
    char* input_file = argv[1];
    char* output_file = argv[2];

    printf("Input File %s", input_file);
    printf("\nOutput File %s", output_file);
    printf("\n");
    
    // read file 
    FILE* input = fopen(input_file, "r");
    FILE* output = fopen(output_file, "w");
    
    char line[1024];
    while (fgets(line, 1024, input)){
        // read line
        char* tmp = strdup(line);

        // get ints from line and sum
        char *pt;
        pt = strtok(tmp,",");
        int sum = 0;
        while (pt != NULL){
            sum = sum + atoi(pt);
            pt = strtok (NULL, ",");
        } 
        
        // convert sum to string
        char sumstr[1024]; 
        sprintf(sumstr, "%d", sum);
       
        // replace new line char with ,
        char* pch = strstr(line, "\n");
        if (pch != NULL) strncpy(pch, ",", 1);

        // concatenate line and sum 
        strcat(line, sumstr);
        //printf("\n%s", line);

        // write to output
        fprintf(output, "%s\n", line);        

        free(tmp);

    } 
    fclose(input);
    fclose(output);

}
