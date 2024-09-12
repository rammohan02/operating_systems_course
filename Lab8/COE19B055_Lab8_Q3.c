#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>

int main()
{
	int pipefds[2];
	int returnstatus;
	int pid, fd, fd1, fd2;
	
	char writemessage[100], readmessage[100];
	
	returnstatus = pipe(pipefds);
	
	if(returnstatus < 0)
	{
		printf("Failed to create pipe\n");
		return 0;
	}
	
	pid = fork();
	if(pid==0)
	{
		fd = open("output1.txt", O_RDWR | O_CREAT, 0666);
		fd1 = open("error.txt", O_RDWR | O_CREAT, 0666);
		printf("We will print output in output1.txt\n");
		read(pipefds[0], readmessage, sizeof(readmessage));
		dup2(fd, STDOUT_FILENO);
		printf("Child process - Reading from pipe - Message is %s", readmessage);
		dup2(fd1, 2);
		//printf("Stderr\n");
		execlp("la", "ls", NULL);
	}
	else
	{
		//printf("Paren process-Enter message: ");
		
		fd = open("input.txt", O_RDONLY);
		
		if(dup2(fd, 0)<0)
		{
			printf("Unable to duplicate file descriptor.");
		    exit(EXIT_FAILURE);
		}
		
		fgets(writemessage, 100, stdin);
		printf("Parent process - Writing to pipe(Read input from input.txt) - Message is %s", writemessage);
		write(pipefds[1], writemessage, sizeof(writemessage));
	}
}
