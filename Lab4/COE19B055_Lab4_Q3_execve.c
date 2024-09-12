#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char* args[] = {NULL};
    char *const env = {NULL};
    execve("./COE19B055_Lab4_Q3_a", args, NULL);
    printf("In COE19B055_Lab4_Q3_execve\n");
}