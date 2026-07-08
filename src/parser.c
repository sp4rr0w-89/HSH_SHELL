#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char **parse(char tokens[], int *length){
    char *ptr = strtok(tokens, " ");
    char **str_array = malloc(25 *sizeof(char *));
    if(str_array == NULL) return NULL;

    int count =0;
    for(int i = 0; i < 25; i++){
        if(ptr == NULL){
            break;
        }
        str_array[i] =  strdup(ptr);
        count++;
        ptr = strtok(NULL, " ");
        }   

    *length = count;
    return str_array;

}