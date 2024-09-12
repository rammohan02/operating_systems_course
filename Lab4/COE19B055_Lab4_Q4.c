#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int n, sum_odd=0, sum_even=0, i;

    printf("Enter n: ");
    scanf("%d", &n);

    while (n<1)
    {
        printf("Enter a positive number: ");
        scanf("%d", &n);
    }

    pid = fork();

    if(pid<0){
        printf("Error in fork process\n");
    }else if(pid==0){
        for(i=1; i<=n; i=i+2)
        {
            sum_odd = sum_odd + i;
        }
        printf("Sum of ODD is: %d\n", sum_odd);
    }else if(pid>0){
        for(i=2; i<=n; i=i+2)
        {
            sum_even = sum_even + i;
        }
        printf("Sum of EVEN is: %d\n", sum_even);
    }

    
}