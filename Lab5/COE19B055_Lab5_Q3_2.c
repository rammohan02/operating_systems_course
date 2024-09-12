#include<stdio.h>
#include<fcntl.h>								//This header has open and close function

int main()
{
	int fd;
	
	fd = open("sample.txt", O_RDWR);			//Return <0 if failed else >0 if success
	
	//O_RDONLY - Read only
	//O_WRONLY - Write only
	//O_RDWR   - Read and Write
	//O_CREATE - create a file if doesnot exist
	//O_EXCl   - Prevent creation if already exist
	
	if(fd<0)
	{
		printf("Failed to open file\n");
		return 0;
	}
	
	printf("Opened fd=%d\n", fd);
	
	close(fd);			//close corresponding fd
	
}
