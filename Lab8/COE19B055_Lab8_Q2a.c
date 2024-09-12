#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
	int pipefds[2];
	int returnstatus;
	int pid;
	
	char writemessage[100], readmessage[100];
	
	returnstatus = pipe(pipefds);
	
	if(returnstatus < 0)
	{
		printf("Failed to create pipe\n");
		return 0;
	}
	
	pid = fork();
	//printf("This is a simplex communication where parent process can write and child process can only read what parent has written\n");
	if(pid==0)
	{
		read(pipefds[0], readmessage, sizeof(readmessage));
		printf("Child process - Reading from pipe - Message is %s\n", readmessage);
	}
	else
	{
		printf("Paren process-Enter message: ");
		fgets(writemessage, 100, stdin);
			
		printf("Parent process - Writing to pipe - Message is %s\n", writemessage);
		write(pipefds[1], writemessage, sizeof(writemessage));
	}
}
