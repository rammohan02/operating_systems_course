#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<time.h>


int main()
{
	int pid1, pid2, pid3;
	
	srand(time(0));
	//pid1 = rand()%10;
	//printf("%d\n", pid1);
	pid1 = fork();
	//pid2 = fork();
	//pid3 = fork();
	
	if(pid1 == 0)
	{
		printf("Child Process\n");
		//printf("Child process with ID=%d terminated %d\n", getpid(), getppid());
		sleep(rand()%10);
	}
	else
	{
		wait(NULL);
		printf("Child process with ID=%d terminated\n", pid1);
		
		pid2=fork();
		if(pid2 == 0)
		{
			printf("Child process\n");
			//printf("Child process with ID=%d terminated %d\n", getpid(), getppid());
			sleep(rand()%10);
		}
		else
		{
			wait(NULL);
			printf("Child process with ID=%d terminated\n", pid2);
			
			pid3 = fork();
			if(pid3==0)
			{
				printf("Child process\n");
				//printf("Child process with ID=%d terminated %d\n", getpid(), getppid());
				sleep(rand()%10);
			}
			else
			{
				wait(NULL);
				//printf("Child process with ID=%d terminated\n", pid1);
				//printf("Child process with ID=%d terminated\n", pid2);
				printf("Child process with ID=%d terminated\n", pid3);
				printf("Parent process exiting\n");
			}
		}
	}
	
}
