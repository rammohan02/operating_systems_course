#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int pid, fd;
	
	fd = open("output.txt", O_CREAT | O_RDWR);
	if(fd<0)
	{
		printf("File unable to create or open\n");
	}
	else
	{
		dup2(fd, 1);
		execlp("ls", "ls", NULL);
		//printf("Hi\n");
	}
}
