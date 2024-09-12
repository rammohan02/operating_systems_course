#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>



sem_t full;
sem_t empty;
sem_t s;
int buffer[5];
int in=0, out=0;


void *producer()
{
	int item, i;
	
	for(i=0; i<5; i++)
	{
		item = rand()%10;
		sem_wait(&empty);
		sem_wait(&s);
		
		buffer[in]=item;
		printf("Producer inserted item %d at %d\n", item, in);
		in = (in+1)%5;
		
		sem_post(&s);
		sem_post(&full);
	}
	return 0;
}


void *consumer()
{
	int item;
	for(int i=0; i<5; i++)
	{
		sem_wait(&full);
		sem_wait(&s);
		
		item = buffer[out];
		printf("Consumer inserted item %d from position %d\n", item, out);
		out = (out+1)%5;
		
		sem_post(&s);
		sem_post(&empty);
	}
}


int main()
{
	srand(time(NULL));
	sem_init(&empty, 0, 5);
	sem_init(&full, 0, 0);
	sem_init(&s, 0, 1);
	
	pthread_t p, c;
	
	int i=0;
	//while(i<5)
	//{
		pthread_create(&p, NULL, producer, NULL);
	//}
	
	i=0;
	//while(i<5)
	//{
		pthread_create(&c, NULL, consumer, NULL);
	//}
	
	//i=0;
	//while(i<5)
	//{
		pthread_join(p, NULL);
	//}
	
	i=0;
	//while(i<5)
	//{
		pthread_join(c, NULL);
	//}
}
