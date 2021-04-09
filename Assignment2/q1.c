#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
 
#define MAX_ARGUMENTS 10
#define EXE_BUFFER_TIME 1
 
int main(int argc, char *argv[])
{
    /* Initialise Variables */
    pid_t pid;
    int stat;
    int n = argc - 1;
    int fileDescriptor[MAX_ARGUMENTS];
 
    if(n < 1){
        /* If no arguments were put */
        printf("No arguments found!\n");
        exit(1);
    } else if(n > MAX_ARGUMENTS){
        printf("Too many arguments! Max arguments: %d.\n", MAX_ARGUMENTS);
        exit(1);
    }
    printf("\nCOMMAND OUTPUTS:\n");
    printf("===========================================\n");
    for(int i=0;i<n;i++)
    {
        char* argument = argv[i+1];
        /* open a file descriptor to check if it is a valid file */
        fileDescriptor[i] = open(argument, O_CLOEXEC);
        /* create direct child processes */
        if(pid = fork() == 0)
        {
            /* if there is no path/file */
            if(fileDescriptor[i] == -1){
                exit(-1);
            }
            /* If there is a path but execute is unsuccessful set exit code to -1*/
            if(execl(argument, argument, NULL) == -1){
                exit(-1);
            }
        } 
    }
    /* Give all process at time to finish execution */
    sleep(EXE_BUFFER_TIME);
    printf("===========================================\n\n");
    for(int i = 0 ; i <n ; i++){
        /* if file cant be opened, just wait for the child to terminate and continue */
        if(fileDescriptor[i] == -1){
            waitpid(pid, &stat, 0);
            printf("Command \"%s\" was not found.\n", argv[i+1]);
            continue;
        } else {
            /* Get the exit code of the terminated process */
            waitpid(pid, &stat, 0);
            /* If child process has already exited and there is a status*/
            if(WIFEXITED(stat)){
                /* If exit code is 0, execl ran successfully. Else, failed */
                if(WEXITSTATUS(stat)==0){
                    printf("Command %s has completed successfully.\n", argv[i+1]);
                } else {
                    printf("Command %s has not completed successfully.\n", argv[i+1]);
                }
            }
        }     
    }
    /* Only printed after all child processes are terminated */
    printf("\nAll done, bye!\n");
}