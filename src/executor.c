#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute(char **tokens){
    

            if(fork()== 0){
                if(execvp(tokens[0], tokens)== -1){
                    printf("\nCommand not part of the hkm system\n");
                    exit(1);
                }
                
            } else {
                wait(NULL);
            }
        
        return 0;
    }
