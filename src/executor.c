#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int execute(char **tokens){

    pid_t pid= fork();
    int status;

            if(pid == 0){
                if(execvp(tokens[0], tokens)== -1){
                    printf("\nCommand not part of the hkm system\n");
                    exit(1);
                }
            } else if(pid < 0){
                perror("Error forking process");
            } else {
                waitpid(pid, &status, 0);
                if(!WIFEXITED(status) && !WIFSIGNALED(status)){
                    printf("Error waiting for child process");
                } 
            }
        
        return 0;
    }
