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
	int status;										//status=0 process read data, status=2 process wrote something
};

int main()
{
	int shmid;
	char buffer[100];
	struct memory *shm;
	key_t  key = ftok("shmfile", 65);
	
	shmid = shmget(key, SIZE, IPC_CREAT|0666);
	
	if(shmid<0)
	{
		printf("Error in creating shared memory\n");
		return 0;
	}
	
	shm = shmat(shmid, NULL, 0);
	
	printf("Enter end to stop process\n");
	int running=1;
	while(1)
	{
		while(shm->status!=1)
			sleep(1);
			
		printf("Read from shared memory: %s", shm->data);
		shm->status = 0;
		
		if(strncmp(shm->data, "end", 3)==0)
		{
			break;
		}
		
		
		printf("Enter message: ");
		fgets(buffer, 100, stdin);
		
		strcpy(shm->data, buffer);
		shm->status=1;
		
		while(shm->status==1)
			sleep(1);
			
		if(strncmp(shm->data, "end", 3)==0)
		{
			break;
		}
	}
	
	/*while(shm->status!=1)
		sleep(1);
	
	printf("Read from shared memory: %s", shm->data);
	shm->status = 0;
	
	printf("Enter message: ");
	fgets(buffer, 100, stdin);
	
	strcpy(shm->data, buffer);
	shm->status=1;
	
	while(shm->status==1)
		sleep(1);*/
	
	shmdt(shm);
	
	shmctl(shmid, IPC_RMID, NULL);
}
