#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>

int main()
{
	int pipefds[2], returnstatus, pid;
	char readmessage[50], writemessage[50], buffer[50];
	
	returnstatus = pipe(pipefds);
	
	if(returnstatus == -1)
	{
		printf("Unable to create pipe\n");
		return 0;
	}
	
	pid = fork();
	
	if(pid<0){
		printf("Unable to execute fork\n");
		return 0;
	}else if(pid==0){
		printf("Child process - Enter message: ");
		fgets(writemessage, 50, stdin);
		
		write(pipefds[1], writemessage, sizeof(writemessage));
	}else{
		read(pipefds[0], readmessage, sizeof(readmessage));
		
		printf("Parent process - Message read is: %s", readmessage);
	}
	
	
}
