#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/tree.h>

int main()
{
    printf("In COE19B055_Lab4_Q2_1\n");
    execlp("ls", "ls", NULL);
    execlp("pstree", "pstree", NULL);
}