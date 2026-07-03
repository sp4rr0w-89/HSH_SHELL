#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"


int main(){
    
    
    char input[1024];
    int arg_len = 0;
    char **tokens; 


   while(1){
        printf("\n\033[32m| hkms_shell:$> \033[0m");

        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Failed to read input");
        } 
        else if (strlen(input) > 1)
        {
            
            input[strcspn(input, "\n")] = '\0';

            tokens = parse(input, &arg_len);

            if(strcmp(tokens[0], "out") == 0 && arg_len == 1){
                return 0;
            }

            for(int i = 0; i < arg_len; i++){
                printf("%s\n", tokens[i]);
            }
            
        }

        
    }
   for(int i = 0; i < arg_len; i++){
        free(tokens[i]);
    }
    free(tokens);
    return 0;
}