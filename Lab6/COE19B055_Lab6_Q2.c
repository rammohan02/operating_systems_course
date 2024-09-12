#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>

void swap(int *p, int *q)
{
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

int main()
{
	int pipefds1[2],pipefds2[2];
	int returnstatus1, returnstatus2;
	int pid;
	
	int writemessage[10], readmessage[10];
	
	returnstatus1 = pipe(pipefds1);
	
	if(returnstatus1 < 0)
	{
		printf("Failed to create pipe1\n");
		return 0;
	}
	
	returnstatus2 = pipe(pipefds2);
	
	if(returnstatus2 < 0)
	{
		printf("Failed to create pipe2\n");
		return 0;
	}
	
	pid = fork();
	
	if(pid == 0)
	{
		close(pipefds1[1]);
		close(pipefds2[0]);
		
		read(pipefds1[0], readmessage, sizeof(readmessage));
		int i, j;
		
		printf("In child process: Read from pipe:  ");
		for(i=0; i<10; i++)
		{
			printf("%d ", readmessage[i]);
		}
		printf("\n");
		
		for(i=9, j=0; i>-1; i--, j++)
		{
			writemessage[j] = readmessage[i];
		}
		
		write(pipefds2[1], writemessage, sizeof(writemessage));
		
	}
	else
	{
		close(pipefds1[0]);
		close(pipefds2[1]);
		
		printf("In parent process: Enter 10 number\n");
		int i, j, min;
		
		for(i=0; i<10; i++)
		{
			printf("Enter num %d: ", i+1);
			scanf("%d", &writemessage[i]);
		}
		
		for(i=0; i<9; i++)
		{
			min = i;
			
			for(j=i; j<10; j++)
			{
				if(writemessage[j] < writemessage[min])
				{
					min = j;
				}
			}
			swap(&writemessage[i], &writemessage[min]);
		}
		
		
		write(pipefds1[1], writemessage, sizeof(writemessage));
		
		read(pipefds2[0], readmessage, sizeof(readmessage));
		
		printf("In parent process: Read from pipe: ");
		for(i=0; i<10; i++)
		{
			printf("%d ", readmessage[i]);
		}
		printf("\n");
		
		
	}
	
}
