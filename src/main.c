#include <stdio.h>
#include <string.h>
#include <signal.h>

void handle_sigint(int sig){
    (void)sig;
    printf("\n\033[32m| hkms_shell:$> \033[0m");
    fflush(stdout); 
}



int main(){
        
    signal(SIGINT, handle_sigint);

    char input[1024];

   while(1){
        printf("\n\033[32m| hkms_shell:$> \033[0m");
        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Exiting...");
            return 0;
        } 

        if (strlen(input) > 1 )
        {
            printf("No parser Yet");     
        }

        
    }
    return 0;
}