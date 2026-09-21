#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "executor.h"
#include <signal.h>
#include <unistd.h>

char* cur_dir();
void handle_sigint(int sig);

int main(){
        
    signal(SIGINT, handle_sigint);

    char input[1024];

    int arg_len = 0;
    CMD_SQ *cmd_arr; 

   while(1){
        
        printf("\n\033[32m| hkms_shell:%s$> \033[0m", cur_dir());

        if(fgets(input,sizeof(input), stdin) == NULL)
        {
            printf("Exiting...");
            return 0;
        } 
        if(strlen(input) > 1000){
            printf("\033[31mInput too long. Try running in sequence!\033[0m");
        } 
        else if (strlen(input) > 1 )
        {
            printf("\n");            
            input[strcspn(input, "\n")] = '\0';
            cmd_arr = parse(input, &arg_len, " ");
            execute(cmd_arr);               
        }

    }
    
//    for(int i = 0; i < arg_len; i++){
//         free(tokens[i]);
//     }
//     free(tokens);
    return 0;
}

char* cur_dir(){
    static char cd[1024];
    if(getcwd(cd, sizeof(cd)) == NULL) perror("Error getting current directory");
    char *pCd = cd;
    return pCd;
}

void handle_sigint(int sig){
    (void)sig;
    printf("\n\033[32m| hkms_shell:%s$> \033[0m", cur_dir());
    fflush(stdout); 
}