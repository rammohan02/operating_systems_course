#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int  arr[100], size, to_find, pre=0;

void swap(int *p, int *q)
{
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

void sort_arr(int a[], int len)
{
    int i, j;
    int go=1;

    while(go)
    {
        for(i=0; i<len-1; i++)
        {
            go=0;
            for(j=0; j<len-1-i; j++)
            {
                if(a[j]>a[j+1])
                {
                    swap(&arr[j], &arr[j+1]);
                    go=1;
                }
            }
        }
    }
}

void *binary_search(void *arg)
{
	int id = (int *)arg;
	int l, r;
	
	l = id * (size/4);
	r = (id+1) * (size/4);
	
	//printf("l=%d, r=%d\n", l, r);
	
	
	while(l<r && !pre)
	{
		int mid = (l+r)/2;
		if(arr[mid]==to_find)
		{
			pre = 1;
			break;
		}
		
		if(arr[mid] < to_find)
		{
			l = mid+1;
		}
		else
		{
			r = mid-1;
		}
		
	}
	
}


int main()
{
	int i, *ptr;
	
	printf("Enter size of array(<100): ");
	scanf("%d", &size);
	
	for(i=0; i<size; i++)
	{
		printf("Enter element %d: ", i+1);
		scanf("%d", &arr[i]);
	}
	
	sort_arr(arr, size);
	
	printf("Enter element to find: ");
	scanf("%d", &to_find);
	
	ptr = &arr[0];
	
	pthread_t t1, t2, t3, t4;
	
	pthread_create(&t1, NULL, binary_search, (void *)0);
	pthread_create(&t2, NULL, binary_search, (void *)1);
	pthread_create(&t3, NULL, binary_search, (void *)2);
	pthread_create(&t4, NULL, binary_search, (void *)3);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	
	if(pre)
	{
		printf("Element is present\n");
	}
	else
	{
		printf("Element not present\n");
	}
}
