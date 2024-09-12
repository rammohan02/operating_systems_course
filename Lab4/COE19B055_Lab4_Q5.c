#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void swap(int *p,int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}

int main()
{
    pid_t pid;
    int n, i, j, arr[10];

    i = 0;
    while (i<10)
    {
        printf("Enter a number %d : ", i+1);
        scanf("%d", &arr[i]);
        i++;
    }

    pid = fork();

    if(pid<0){
        printf("Error in fork process\n");
    }else if(pid==0){
        for(i=0; i<9; i++)
        {
            for(j=0; j<9-i; j++)
            {
                if(arr[j]<arr[j+1])
                {
                    swap(&arr[j], &arr[j+1]);
                }
            }
        }
        printf("Descending order of given is: ");
        for(i=0; i<10; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }else if(pid>0){
        for(i=0; i<9; i++)
        {
            for(j=0; j<9-i; j++)
            {
                if(arr[j]>arr[j+1])
                {
                    swap(&arr[j], &arr[j+1]);
                }
            }
        }
        wait(NULL); /* OR  waitpid(-1, NULL, 0);*/
        printf("Ascending order of given is: ");
        for(i=0; i<10; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}