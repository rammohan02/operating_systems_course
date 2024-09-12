#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char* args[] = {NULL};
    execv("./COE19B055_Lab4_Q2_1", args);
}