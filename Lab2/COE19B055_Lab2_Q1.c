//COE19B055
//K. Ram Mohan
#include<stdio.h>
#include<stdlib.h>
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
    int total_process, i;

    int process_id[SIZE], arr_time[SIZE], burst_time[SIZE], time=0;
    float tot_waiting_time=0, tot_trt=0;

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
    }

    sort_arr(process_id, arr_time, burst_time, total_process);

    int completion_time[SIZE], waiting_time[SIZE], turn_arnd_time[SIZE];

    for(i=0; i<total_process; i++)
    {
        //completion_time[i] = ( (i==0 && arr_time[i]>0) ? arr_time[i]+burst_time[i] : burst_time[i])+ ((i==0) ? 0 : completion_time[i-1]);
        //for initial one and for cpu idle time one
        if(time==0 || time<arr_time[i])
        {
            completion_time[i] = arr_time[i] + burst_time[i];
        }
        else
        {
            completion_time[i] = completion_time[i-1] + burst_time[i];
        }
        time = completion_time[i];
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


    /*for(i=0; i<total_process; i++)
    {
        printf("%d \n", completion_time[i]);
    }*/


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
    printf("Average turn around time is: %f", avg_trt);

}
