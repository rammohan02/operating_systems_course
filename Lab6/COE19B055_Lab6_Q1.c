#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>

int main()
{
	int pipefds1[2], pipefds2[2];
	int returnstatus1, returnstatus2;
	int pid;
	
	char writemessage[50], readmessage[50], buffer[50];
	
	returnstatus1 = pipe(pipefds1);
	
	if(returnstatus1 == -1)
	{
		printf("Failed to create pipe1\n");
		return 0;
	}
	
	returnstatus2 = pipe(pipefds2);
	
	if(returnstatus2 == -1)
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
		strcpy(buffer, readmessage);
		
		int i, sum=0;
		//-1 is given to exclude the line feed character
		for(i=0; i<strlen(buffer)-1; i++)
		{
			sum = sum + buffer[i];
		}
		
		sprintf(writemessage, "%d", sum);
		
		write(pipefds2[1], writemessage, sizeof(writemessage));
	}
	else
	{
		close(pipefds1[0]);
		close(pipefds2[1]);
		
		printf("In parent process: Enter the string: ");
		fgets(buffer, 50, stdin);
		
		strcpy(writemessage, buffer);
		
		write(pipefds1[1], writemessage, sizeof(writemessage));
		
		read(pipefds2[0], readmessage, sizeof(readmessage));
		
		printf("In parent process: Sum read from pipe is: %s\n", readmessage);
	}
}

