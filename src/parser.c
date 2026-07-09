#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

#define TOK_SIZE 64


char **parse(char tokens[], int *length){

    int capacity = TOK_SIZE;
    int count = 0;
    char *token = strtok(tokens, " ");

    char **str_array = malloc(TOK_SIZE *sizeof(char *));

    if(str_array == NULL) return NULL;
    

    while(token != NULL){
        str_array[count] = token;
        count++;

        if(count +1 >= capacity){

            printf("\nResizing...\nCount: %d; Capacity: %d\n", count, capacity);
            capacity += TOK_SIZE;
            str_array = realloc(str_array, capacity * sizeof(char *));
            if(str_array == NULL) {
                perror("Error reallocating token buffer");
                break;
            }

        }
        token = strtok(NULL, " ");

    }   
        
    str_array[count] = NULL;
    *length = count;
    return str_array;

}