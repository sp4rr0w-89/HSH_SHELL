#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

typedef struct {
    char name[25];
    int (*func)(char **tokens, int args);
} CMD;

int sh_cd(char **tokens, int args);
int sh_exit(char **tokens, int args);
int sh_export(char **tokens, int args);

int run_builtin(char **tokens){
    
    CMD commands[]=
    {
        {.name = "cd", .func = sh_cd},
        {.name = "exit", .func = sh_exit},
        {.name = "export", .func = sh_export}
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

int sh_exit(char **tokens, int args){
    if(args > 2){
        printf("exit:: Too many argumets\n");
        return 0;
    }
    if(tokens[1]!= NULL){
        exit(atoi(tokens[1]));
    }

    exit(0);
}

int sh_export(char **tokens, int args){
    int export_args = 0;
    char **env_variable = parse(tokens[1], &export_args, "=");
    
    if(export_args<2){
        printf("Please provide the name and value of the variable to set. Format: name=value\n");
        return 1;
    } else if(args > 2){
        printf("Too many arguments");
        return 1;
    }
    if(setenv(env_variable[0], env_variable[1], 0) != 0){
        printf("Error setting environmental variable");
    } 
    return 0;
}

