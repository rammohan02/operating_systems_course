#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char* args[] = {NULL};
    execl("./COE19B055_Lab4_Q3_a", "./COE19B055_Lab4_Q3_a", args);
    printf("In COE19B055_Lab4_Q3_execl\n");
}