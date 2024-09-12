#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


void *thread_fn(void* arg)
{
	int *end = (int*) arg;
	int i=0;
	
	printf("In thread\n");
	while(i<=*end)
	{
		printf("%d\n", i);
		i++;
	}
	return NULL;
}

int main()
{
	int n;
	printf("In main- Enter n: ");
	scanf("%d", &n);
	
	pthread_t t1, t2, t3, t4;
	
	pthread_create(&t1, NULL, thread_fn, (void *)&n);
	
	pthread_join(t1, NULL);
	
	return 0;
}
