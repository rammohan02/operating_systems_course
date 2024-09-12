#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/tree.h>

int main()
{
    printf("In COE19B055_Lab4_Q3_a\n");
    for(int i=0; i<2; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
}