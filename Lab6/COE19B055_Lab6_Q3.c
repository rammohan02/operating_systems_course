#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<math.h>

int armstrong(int num)
{
	int digits, sum, temp, rem;
	digits = 0;
	sum = 0;
	temp = num;
	while(temp>0)
	{
		temp = temp/10;
		digits++;
	}
			
	temp = num;
			
	while(temp>0)
	{
		rem = temp%10;
		sum = sum + pow(rem, digits);
		temp = temp/10;
	}
			
	if(sum == num)
	{
		return  1;
	}
	else
	{
		return 0;
	}
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
		int i, j, digits, temp, rem, sum;
		
		for(i=0; i<10; i++)
		{
			writemessage[i] = armstrong(readmessage[i]);
			/*digits = 0;
			sum = 0;
			temp = readmessage[i];
			while(temp>0)
			{
				temp = temp/10;
				digits++;
			}
			
			temp = readmessage[i];
			
			while(temp>0)
			{
				rem = temp%10;
				sum = sum + pow(rem, digits);
				temp = temp/10;
			}
			
			if(sum == readmessage[i])
			{
				writemessage[i] = 1;
			}
			else
			{
				writemessage[i] = 0;
			}*/
		}
		
		write(pipefds2[1], writemessage, sizeof(writemessage));
	}
	else
	{
		close(pipefds1[0]);
		close(pipefds2[1]);
		
		printf("In parent process: Enter 10 number\n");
		int i;
		
		for(i=0; i<10; i++)
		{
			printf("Enter num %d: ", i+1);
			scanf("%d", &writemessage[i]);
		}
		
		write(pipefds1[1], writemessage, sizeof(writemessage));
		
		read(pipefds2[0], readmessage, sizeof(readmessage));
		
		printf("In parent process: Result = 1 if armstrong 0 if not\n");
		for(i=0; i<10; i++)
		{
			printf("%d - %d \n", writemessage[i], readmessage[i]);
		}
	}
}
