#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void *thread_function(void *arg)
{
	int *ptr = (int *)arg;
	int sum=0, n ,i;
	int *result = malloc(sizeof(int));
	
	/*for(i=0; i<5; i++)
	{
		printf("arr[%d] is %d\n", i, *(ptr+i));
	}*/
	
	for(i=0; i<5; i++)
	{
		sum = sum + (*(ptr+i));
	}
	
	//printf("In thread sum is:%d\n", sum);
	*result = sum;
	pthread_exit((void *)result);
	//pthread_exit((void *)&sum);									//we can't directly pass local variable refernece because it will be removed from stack once funcion is returned
}

int main()
{
	int arr[5], i, *ptr;
	
	for(i=0; i<5; i++)
	{
		printf("Enter arr[%d]: ", i);
		scanf("%d", &arr[i]);
	}
	
	ptr = &arr[0];
	
	/*for(i=0; i<5; i++)
	{
		printf("arr[%d] is %d\n", i, *(ptr+i));
	}*/
	
	pthread_t a_thread;
	int *sum;
	
	pthread_create(&a_thread, NULL, thread_function, (void *)ptr);
	
	//pthread_join expects void ** so we are passing reference of sum which is a pointer results in double pointer, then type casting to void
	pthread_join(a_thread, (void **)&sum);
	
	printf("Thread returned %d\n", *(int *)sum);
	free(sum);
	return 0;
}


