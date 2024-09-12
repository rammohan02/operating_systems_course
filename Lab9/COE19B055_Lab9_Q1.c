#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int sum[5];

void *thread_fn(void *arg)
{
	int id= (int *) arg;
	int start = (id)*200;
	start = start+1;
	int i=0;
	
	while(i<200)
	{
		sum[id]+=(i+start);
		i++;
	}
	return NULL;
}

int main()
{
	pthread_t t1, t2, t3, t4, t5;
	
	pthread_create(&t1, NULL, thread_fn, (void *)0);
	pthread_create(&t2, NULL, thread_fn, (void *)1);
	pthread_create(&t3, NULL, thread_fn, (void *)2);
	pthread_create(&t4, NULL, thread_fn, (void *)3);
	pthread_create(&t5, NULL, thread_fn, (void *)4);
	
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	
	printf("Sum of numbers from   1 to  200 calculated by thread 1 is %d\n", sum[0]);
	printf("Sum of numbers from 200 to  400 calculated by thread 2 is %d\n", sum[1]);
	printf("Sum of numbers from 400 to  600 calculated by thread 3 is %d\n", sum[2]);
	printf("Sum of numbers from 600 to  800 calculated by thread 4 is %d\n", sum[3]);
	printf("Sum of numbers from 800 to 1000 calculated by thread 5 is %d\n", sum[4]);
	
	printf("Sum of all 1000 numbers is %d\n", sum[0]+sum[1]+sum[2]+sum[3]+sum[4]);
	return 0;
}
