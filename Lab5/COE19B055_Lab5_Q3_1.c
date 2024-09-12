#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>								//This header has opendir and readdir and closedir as well
#include <errno.h>

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dirp;						//to acces files throught that directory
	char buffer[50];
	
	/*printf("Enter directory name: ");
	fgets(buffer, 0, stdin);*/
	
	if (argc != 2) {
		printf("Enter directory name in format: ./Directory name\n");
		return 0;
    }
	
	dp = opendir(argv[1]);						//Returns a DIR pointer to directory if exists else return NULL
	
	if(dp==NULL)
	{
		printf("NO such directory exists\n");
		return 0;
	}
	while((dirp=readdir(dp))!=NULL)
	{
		printf("%s\n", dirp->d_name);
	}
	
	closedir(dp);
	return 0;
}

