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
		
		printf("Child process - Write a message(to pipe2): ");
		fgets(buffer, 20, stdin);
		
		int n = strlen(readmessage);
		
		int i, j=0;
		for(i=0; i<n-1; i++)
		{
			writemessage[j] = readmessage[i];
			j++;
		}
		writemessage[j] = ' ';
		j++;
		for(i=0; i<strlen(buffer)-1; i++)
		{
			writemessage[j] = buffer[i];
			j++;
		}
		//strcat(readmessage, buffer);
		//strcpy(writemessage, readmessage);
		
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
