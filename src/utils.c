#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **arr_to_ptr(char tokens[][1024], int n_toks){

    char **tok_store = malloc((n_toks +1) * sizeof(char *)); 
    if(tok_store == NULL ){
        printf("Error allocating token store memory\n");
        exit(1);
    }

    for( int i =0; i < n_toks; i++){
        tok_store[i] = malloc(strlen(tokens[i]) + 1);
        if(tok_store[i] == NULL) {
            printf("Error accessing token pointer\n");
            exit(1);
        }
        strcpy(tok_store[i], tokens[i]);
    }

    tok_store[n_toks]=NULL;
    return tok_store;

}

int dbptr_cleaner(char **arr){
    int count = 0;
    if(arr == NULL){
        printf("Error freeing memory\n");
        exit(1);
    }

    while (arr[count] != NULL){
        free(arr[count]);
        count++;
    }
    free(arr);
    return 0;
}
