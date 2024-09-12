#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    pid_t pid;

    pid = fork();
    
    if(pid==0)
    {
        printf("In child process\n");
    }

    int status;

    if(pid>0)
    {
        waitpid(pid, &status, 0);

        if(WIFEXITED(status))
        {
            printf("Child Process is exited safely\n");
        }
    }
    return(0);
}