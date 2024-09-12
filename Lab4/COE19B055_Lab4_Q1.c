#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    

    if(pid<0){
        printf("Error in fork call");
    }else if (pid==0)
    {
        fork();
        fork();
        printf("Process id of me is %d\n", getpid());
        printf("Process id of my parent is %d\n", getppid());
    }else if(pid>0){
        fork();
        printf("Process id of mw is %d\n", getpid());
    }
    return(0);
}
