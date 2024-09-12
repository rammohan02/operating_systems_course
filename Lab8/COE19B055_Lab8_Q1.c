#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define SIZE 100

void swap(int *p,int *q)
{
	int temp;
	temp=*p;
	*p=*q;
	*q=temp;
}

//function to sort based on arrival time
void sort_arr(int id[], int arr[], int burst_time[] , int size)
{
	int i, j;
	int go=1;
	while(go)
	{
		for(i=0; i<size-1; i++)
		{
			go=0;
			for(j=0; j<size-1-i; j++)
			{
				if(arr[j]>arr[j+1])
				{
					swap(&arr[j], &arr[j+1]);
					swap(&id[j], &id[j+1]);
					swap(&burst_time[j], &burst_time[j+1]);
					go=1;
				}
			}
		}
	} 
}
 
 
int main()
{
	int total_process, i, j;
	int process_id[SIZE], arr_time[SIZE], burst_time[SIZE], completed[SIZE], c_time=0, index;
	float tot_waiting_time=0, tot_trt=0, response_ratio, temp;
	
	printf("Enter no of process: ");
	scanf("%d", &total_process);
	for(i=0; i<total_process; i++)
	{
		printf("Process_id of process %d: ", i+1);
		scanf("%d", &process_id[i]);
		printf("Arrival time of process %d: ", i+1);
		scanf("%d", &arr_time[i]);
		printf("Burst time of process %d: ", i+1);
		scanf("%d", &burst_time[i]);
		completed[i]=0;
	}
	
	sort_arr(process_id, arr_time, burst_time, total_process);
	int completion_time[SIZE], waiting_time[SIZE], turn_arnd_time[SIZE];
	
	for(i=0; i<total_process; i++)
	{
		response_ratio = -999;
		c_time= ((i==0 || c_time<arr_time[i]) ? arr_time[i] : c_time);
		printf("%d-ctime\n", c_time);

		for(j=0; j<total_process; j++)
		{
			if(c_time>=arr_time[j] && completed[j]!=1)
			{
				temp = (float)((c_time-arr_time[j])+burst_time[j])/(float)(burst_time[j]);
				
				if(temp>response_ratio)
				{
					response_ratio = temp;
					index=j;
				}
			}
		}
		
		c_time=c_time+burst_time[index];
		completed[index]=1;
		
		completion_time[index]=c_time;
	}
	
	for(i=0; i<total_process; i++)
    {
        turn_arnd_time[i] = completion_time[i] - arr_time[i];
        tot_trt = tot_trt + turn_arnd_time[i];
    }

    for(i=0; i<total_process; i++)
    {
        waiting_time[i] = turn_arnd_time[i] - burst_time[i];
        tot_waiting_time = tot_waiting_time + waiting_time[i];
    }
	
	printf("Processes   arrival_time   Burst time  completion time   Turn around time   Waiting time\n");
    for(i=0; i<total_process; i++)
    {
        printf("%d", process_id[i]);
        printf("\t \t %d", arr_time[i]);
        printf("\t \t %d", burst_time[i]);
        printf("\t \t %d", completion_time[i]);
        printf("\t \t %d", turn_arnd_time[i]);
        printf("\t \t %d \n", waiting_time[i]);
    }
    
    float avg_wait = tot_waiting_time/total_process;
    float avg_trt = tot_trt/total_process;
    printf("Average waiting time is : %f\n", avg_wait);
    printf("Average turn around time is: %f\n", avg_trt);
}






















