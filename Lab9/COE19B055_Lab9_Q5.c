#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>


sem_t s;
int x=1;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void *fun1(void * arg)
{
	int *t=(int *)arg;
	printf("Statement a1\n");
	//sem_wait(&s);
	pthread_mutex_lock(&lock);
	x++;
	printf("Thread1 - X updated to %d\n", x);
	
	if(*t%2==0)
	{
		pthread_cond_wait(&cond1, &lock);
	}
	
	x++;
	printf("Statemetn a2\n");
	printf("Thread 1 - X value %d\n", x);
	
	if(*t%2==1)
	{
		pthread_cond_signal(&cond2);
	}
		
	//sem_post(&s);
	pthread_mutex_unlock(&lock);
}


void *fun2(void* arg)
{
	int *t = (int *)arg;
	//sem_wait(&s);
	pthread_mutex_lock(&lock);
	printf("Statement b1 \n");
	x--;
	printf("Thraed 2 - X values updated to %d\n", x);
	
	if(*t%2==1)
	{
		pthread_cond_wait(&cond2, &lock);
	}
	
	printf("Statement b2\n");
	
	printf("Thread 2 - X value updated to %d\n", x);
	
	if(*t==0)	
	{
		pthread_cond_signal(&cond1);
	}

	
	//sem_post(&s);
	pthread_mutex_unlock(&lock);
	
}


int main()
{
	srand(time(NULL));
	int t = rand()%10 + 1;

	pthread_t p1, p2;
	
	sem_init(&s, 0, 1);
	
	//printf("%d %d\n", t, t%2);
	
	printf("Initially x is %d\n", x);
	
	pthread_create(&p1, NULL, fun1, (void *)&t);
	pthread_create(&p2, NULL, fun2, (void *)&t);
	
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	
	/*if(t%2==0)
	{
		printf("a\n");
		pthread_create(&p1, NULL, fun1, (void *)&t);
		pthread_create(&p2, NULL, fun2, (void *)&t);
	}
	else
	{
		printf("b\n");
		pthread_create(&p2, NULL, fun2, (void *)&t);
		pthread_create(&p1, NULL, fun1, (void *)&t);
	}
	
	if(t%2==0)
	{
		pthread_join(p1, NULL);
		pthread_join(p2, NULL);
	}
	else
	{
		pthread_join(p2, NULL);
		pthread_join(p1, NULL);
	}
	
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond1);*/
	
}
