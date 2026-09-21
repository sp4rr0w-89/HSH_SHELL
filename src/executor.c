#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "builtins.h"
#include "parser.h"
#include "utils.h"

//helper functions
void run_cmd(char **tokens);
int run_redirection(char filename[], char **tokens, int trait);

int execute(CMD_SQ *cmd_arr){
    extern int n_o_cmd;
    
    for(int i = 0; i< n_o_cmd; i++){

        for(int j = 0; j< n_o_cmd; j++){
            if(cmd_arr[j].trait == 3){
                printf("\nhsh Version 1.0 currently doesn't support piping. Try redirection instead\n");
                return 0;
            }
        }

        char **tokens = arr_to_ptr(cmd_arr[i].tokens, cmd_arr[i].tok_count);
        if(cmd_arr[i].trait == 1 || cmd_arr[i].trait == 2)
        {
            run_redirection(cmd_arr[(i +1)].tokens[0], tokens, cmd_arr[i].trait);
            i++;
        } 
        else 
        {
            run_cmd(tokens);
            dbptr_cleaner(tokens);
        }
    }
    return 0;
}

void run_cmd(char **tokens){

    if(run_builtin(tokens) == 0){
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
    }
}

int run_redirection(char filename[], char **tokens, int trait){

    int flag = trait == 1? O_WRONLY | O_CREAT | O_TRUNC : O_WRONLY | O_CREAT | O_APPEND;
    char *fnamePtr = filename;
            if(fnamePtr == NULL){
                printf("Error accessing output file. Please provide an output file\n");
                return 1;
            }

            int dest = open(fnamePtr,flag, 0644);
            int output = dup(STDOUT_FILENO);

            if(dest < 0 || output < 0){
                printf("Error opening file. Does the file exist?");
                close(dest);
                return 1;
            }

            if (dup2(dest, 1) < 0){
                printf("Error switching stdout");
                close(dest);
                return 1;
            }

            run_cmd(tokens);

            close(dest);

            if (dup2(output, STDOUT_FILENO) < 0){
                printf("Error switching stdout");
                close(dest);
                exit(1);
            }

            dbptr_cleaner(tokens);
            return 0;
}
