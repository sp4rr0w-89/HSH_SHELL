#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

#define TOK_SIZE 64

int n_o_cmd =0;

CMD_SQ *eval(char **tok_array, int tok_count,int cmd_count);
int n_cmd(char **toks);
int assign_flag(char flag[]);

CMD_SQ *parse(char tokens[], int *length, char delim[]){

    int capacity = TOK_SIZE;
    int count = 0;
    char *token = strtok(tokens, delim);

    char **str_array = malloc(TOK_SIZE *sizeof(char *));

    if(str_array == NULL) return NULL;
    
    while(token != NULL){
        str_array[count] = token;
        count++;

        if(count +1 >= capacity){

            capacity += TOK_SIZE;
            str_array = realloc(str_array, capacity * sizeof(char *));
            if(str_array == NULL) {
                perror("Error reallocating token buffer");
                free(str_array);
                break;
            }

        }
        token = strtok(NULL, delim);

    } 
    str_array[count] = NULL;
    
    int cmd_count = n_cmd(str_array);   
    CMD_SQ *cmd_arr = eval(str_array, count, cmd_count);
    n_o_cmd = cmd_count; 
    return cmd_arr;


}

CMD_SQ *eval(char **tok_array, int tok_count,int cmd_count){
    char flags[] = ">|>>";
    CMD_SQ *cmd_arr;
    cmd_arr = malloc(sizeof(CMD_SQ) * cmd_count);

    if(tok_count > 64) {
        printf("Too many arguments\n");
        exit(1);
    }

    int j = 0;
    for(int i = 0; i < cmd_count; i++){

        int k = 0;
        for(; j < tok_count; j++){
            if(strstr(flags,tok_array[j]) != NULL){
                cmd_arr[i].trait = assign_flag(tok_array[j]);
                j++; 
                break; 

            } else {
                cmd_arr[i].trait = assign_flag(tok_array[j]);
                strcpy(cmd_arr[i].tokens[k], tok_array[j]);
                k++;
            }
        }
        cmd_arr[i].tok_count = k;
    } 
    return cmd_arr;
}

int n_cmd(char **toks){
    char flags[] = ">|>>";
    int count = 1;
    int i =0;

    while(toks[i] != NULL){

        if(strstr(flags, toks[i]) != NULL){
            count++;
        }
        i++;
    }

    return count;
}

int assign_flag(char flag[]){

    if (strcmp(flag, ">") == 0)
    {
       return 1;
    }
    else if (strcmp(flag, ">>") == 0)
    {
        return 2;
    }
    else if (strcmp(flag, "|") == 0)
    {
       return 3; 
    }
    else return 0;
    
}