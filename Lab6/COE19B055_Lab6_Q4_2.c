#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#define SIZE 100

struct memory{
	char data[SIZE];
	int status;									//status=0 process read data, status=2 process wrote something
	int pal;
};

int main()
{
	int shmid;
	struct memory *shm;
	char buffer[100], buffer1[100];
	
	key_t key = ftok("shmfile", 65);
	
	shmid = shmget(key, SIZE, IPC_CREAT|0666);
	
	if(shmid<0)
	{
		printf("Creation of shared memory failed\n");
		return 0;
	}
	
	shm = shmat(shmid, NULL, 0);
	
	printf("Enter end-end to end chat\n");
	
	while(1)
	{
		while(shm->status!=1)
		sleep(1);
		
		printf("Read from shared memory: %s", shm->data);
		shm->status = 0;
		
		if(strncmp(shm->data, "end-end", 7)==0)
		{
			break;
		}
		
		int i, len, temp = 1;
		
		len = strlen(shm->data) - 1;
		strncpy(buffer, shm->data, len);
		
		for(i=0; i<(len)/2; i++)
		{
			if(strncmp(&buffer[i], &buffer[len-1-i], 1)!=0)
			{
				temp = 0;
			}
			//printf("%c\n", buffer[len - 1 - i]);
		}
		
		
		if(temp==1)
		{
			//strncpy(buffer, "1", 1);
			printf("It is a palindrome :%d\n", temp);
			shm->pal = 1;
		}else
		{
			//strncpy(buffer, "0", 1);
			printf("It is not a palindrome :%d\n", temp);
			shm->pal = 0;
		}
		
		//it is just to prevent to exit the code
		printf("Enter 1 if given is palindrome or 0(or else print enter to continue): ");
		fgets(buffer, 100, stdin);
		
		//strcpy(shm->data, buffer);
		shm->status=1;
		
		while(shm->status==1)
			sleep(1);
	}
	
	
		
	/*while(shm->status!=1)
		sleep(1);
	
	printf("Read from shared memory: %s", shm->data);
	shm->status = 0;
	
	int i, len, temp = 1;
	
	len = strlen(shm->data) - 1;
	strncpy(buffer, shm->data, len);
	
	for(i=0; i<(len)/2; i++)
	{
		if(strncmp(&buffer[i], &buffer[len-1-i], 1)!=0)
		{
			temp = 0;
		}
		//printf("%c\n", buffer[len - 1 - i]);
	}
	
	
	if(temp==1)
	{
		//strncpy(buffer, "1", 1);
		printf("It is a palindrome :%d\n", temp);
		shm->pal = 1;
	}else
	{
		//strncpy(buffer, "0", 1);
		printf("It is not a palindrome :%d\n", temp);
		shm->pal = 0;
	}
	
	printf("Enter 1 if given is palindrome or 0: ");
	fgets(buffer, 100, stdin);
	
	strcpy(shm->data, buffer);
	shm->status=1;
	
	while(shm->status==1)
		sleep(1);*/



	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	
}
