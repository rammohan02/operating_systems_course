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
	char buffer[100];
	
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
		printf("Enter message: ");
		fgets(buffer, 100, stdin);
		
		strcpy(shm->data, buffer);
		shm->status = 1;
		
		if(strncmp(shm->data, "end-end", 7)==0)
		{
			break;
		}
		
		while(shm->status==1)
			sleep(1);
		
		while(shm->status==0)
			sleep(1);
		
		//printf("Read from shared memory: %s", shm->data);
		
		if(shm->pal == 1)
		{
			printf("It is a palindrome\n");
		}
		else
		{
			printf("It is not a palindrome\n");
		}
		shm->status=0;
	}
	
	/*printf("Enter message: ");
	fgets(buffer, 100, stdin);
	
	strcpy(shm->data, buffer);
	shm->status = 1;
	
	while(shm->status==1)
		sleep(1);
	
	while(shm->status==0)
		sleep(1);
	
	printf("Read from shared memory: %s", shm->data);
	
	if(shm->pal == 1)
	{
		printf("It is a palindrome\n");
	}
	else
	{
		printf("It is not a palindrome\n");
	}
	shm->status=0;*/
	
	
	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
}
