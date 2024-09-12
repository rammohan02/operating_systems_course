#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>

int main()
{
	int pipefds1[2], pipefds2[2];											//two pipe descriptors
	int returnstatus1, returnstatus2;										//return status after creating pipes
	int pid;
	char writemessage[20], readmessage[20], buffer[50];

	returnstatus1 = pipe(pipefds1);
	
	if(returnstatus1 == -1)
	{
		printf("Unable to create pipe1\n");
		return 0;
	}
	
	returnstatus2 = pipe(pipefds2);
	
	if(returnstatus2==-1)
	{
		printf("Unable to create pipe2\n");
		return 0;
	}
	
	pid = fork();
	
	if(pid==0)
	{
		close(pipefds1[1]);												//closing write for child in pipe1
		close(pipefds2[0]);												//closing read for child in pipe2
		
		read(pipefds1[0], readmessage, sizeof(readmessage));
		//printf("Child process - read from pipe1: %s", readmessage);
		
		int n = strlen(readmessage);
		
		int j=0;
		for(int i=1; i<n; i++)
		{
			writemessage[j] = readmessage[n-1-i];
			j++;
		}
		
		write(pipefds2[1], writemessage, sizeof(writemessage));
	}
	else
	{
		close(pipefds1[0]);												//closing read for parent in pipe1
		close(pipefds2[1]);												//closing write for parent in pipe2
		
		printf("Parent process - Write to pipe1: ");
		fgets(buffer, 50, stdin);
		
		strcpy(writemessage, buffer);
		
		write(pipefds1[1], writemessage, sizeof(writemessage));
		
		read(pipefds2[0], readmessage, sizeof(readmessage));
		printf("Patent process - Read from pipe2: %s\n", readmessage);
	}
	
	return 0;
}
