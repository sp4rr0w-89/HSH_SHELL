#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include <signal.h>


void handle_sigint(int sig){
    (void)sig;
    printf("\n\033[32m| hkms_shell:$> \033[0m");
    fflush(stdout); 
}



int main(){
        
    signal(SIGINT, handle_sigint);

    char input[1024];

    int arg_len = 0;
    char **tokens; 

   while(1){
        printf("\n\033[32m| hkms_shell:$> \033[0m");

        if(fgets(input,def_BUF_SIZE, stdin) == NULL)
        {
            printf("Exiting...");
            return 0;
        } 
        if(strlen(input) > 1000){
            perror("\033[31mInput too long. Try running in sequence!\033[0m");
        }

        if (strlen(input) > 1 )
        {
            input[strcspn(input, "\n")] = '\0';
            printf("length: %ld", strlen(input));

            tokens = parse(input, &arg_len);

            // for(int i = 0; i < arg_len; i++){
            //     printf("%s\n", tokens[i]);
            // }
            
        }

        
    }
   for(int i = 0; i < arg_len; i++){
        free(tokens[i]);
    }
    free(tokens);
    free(input);
    return 0;
}