#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>


int main()
{
	int pipefds1[2],pipefds2[2];
	int returnstatus1, returnstatus2;
	int pid;
	
	char writemessage[100], readmessage[100];
	
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
		printf("Chid process- Read from parent process: %s", readmessage);
		
		printf("Child process- Enter message: ");
		fgets(writemessage, 100, stdin);
		write(pipefds2[1], writemessage, sizeof(writemessage));
	}
	else
	{
		close(pipefds1[0]);
		close(pipefds2[1]);
		
		printf("Parent process- Enter message: ");
		fgets(writemessage, 100, stdin);
		write(pipefds1[1], writemessage, sizeof(writemessage));
		
		read(pipefds2[0], readmessage, sizeof(readmessage));
		printf("Parent process- Read from child process: %s", readmessage);
		
	}
	
}
