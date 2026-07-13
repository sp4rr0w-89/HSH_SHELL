#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char name[25];
    int (*func)(char **tokens, int args);
} CMD;

int sh_cd(char **tokens, int args);

int run_builtin(char **tokens){
    
    CMD commands[]=
    {
        {.name = "cd", .func = sh_cd},
    };
    
    int n_commands = sizeof(commands) / sizeof(commands[0]);
    int n_tokens = 0;

    while(tokens[n_tokens] != NULL){
        if(tokens[n_tokens] == NULL) break;
        n_tokens++;
    }

        for(int i = 0; i < n_commands; i++){
        if(!strcmp(tokens[0], commands[i].name)){
            commands[i].func(tokens, n_tokens);
            return 1;
            }   
        }
    
    return 0;
}

int sh_cd(char **tokens, int args){
    if(args > 2) {
        printf("Too many arguments. cd takes two arguments\n");
        return 1;

    } else if(tokens[1] == NULL){
        printf("Not enough arguments! cd takes two arguments\n");
        return 1;
    } else if(chdir(tokens[1]) != 0){
        printf("Error changing directory. Does the directory exist?\n");
        return 1;
    }

    return 0;
}

