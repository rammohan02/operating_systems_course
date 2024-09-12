//COE19B055
//K. Ram Mohan
#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
#include "queue.h"

void swap(int *p,int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}

//function to sort based on arrival time
void sort_arr(int id[], int arr[], int burst_time[],int temp_b_time[], int priority[], int len)
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
                if(arr[j]>arr[j+1])
                {
                    swap(&arr[j], &arr[j+1]);
                    swap(&id[j], &id[j+1]);
                    swap(&burst_time[j], &burst_time[j+1]);
                    swap(&priority[j], &priority[j+1]);
                    swap(&temp_b_time[j], &temp_b_time[j+1]);
                    go=1;
                }

                if(arr[j]==arr[j+1])
                {
                    if(priority[j]<priority[j+1])
                    {
                        swap(&arr[j], &arr[j+1]);
                        swap(&id[j], &id[j+1]);
                        swap(&burst_time[j], &burst_time[j+1]);
                        swap(&priority[j], &priority[j+1]);
                        swap(&temp_b_time[j], &temp_b_time[j+1]);
                        go=1;
                    }

                    if(priority[j]==priority[j+1])
                    {
                        if(id[j]>id[j+1])
                        {
                            swap(&arr[j], &arr[j+1]);
                            swap(&id[j], &id[j+1]);
                            swap(&burst_time[j], &burst_time[j+1]);
                            swap(&temp_b_time[j], &temp_b_time[j+1]);
                            swap(&priority[j], &priority[j+1]);
                            go=1;
                        }
                    }
                }
            }
        }
    }
}

void sort_arr_prio( int arr[], int len)
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
                if(arr[j]>arr[j+1])
                {
                    swap(&arr[j], &arr[j+1]);
                    go=1;
                }
            }
        }
    }
}

int index_id(int id, int process_id_arr[], int len)
{
    int i;
    for(i=0; i<len; i++)
    {
        if(process_id_arr[i]==id)
        {
            return i;
        }
    }
    return -1;
}

int pre(int arr[], int len, int val)
{
    int j;
    for(j=0; j<len; j++)
    {
        if(arr[j] == val)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int total_process, i, j;
    struct queue process_id;
    process_id.enqueue=enqueue1;
    process_id.dequeue=dequeue1;
    process_id.display=display1;
    process_id.empty=empty1;
    process_id.front=-1;
    process_id.rear=-1;

    int process_id_arr[SIZE], arr_time[SIZE], burst_time[SIZE], temp_b_time[SIZE], in_queue[SIZE], in_queue_len=0, priority[SIZE], c_time=0, element;
    int index, index1, start=0;
    float tot_waiting_time=0, tot_trt=0;

    printf("Enter no of process: ");
    scanf("%d", &total_process);

    for(i=0; i<total_process; i++)
    {
        printf("Process_id of process %d: ", i+1);
        scanf("%d", &process_id_arr[i]);
        printf("Arrival time of process %d: ", i+1);
        scanf("%d", &arr_time[i]);
        printf("Burst time of process %d: ", i+1);
        scanf("%d", &element);
        burst_time[i]=element;
        temp_b_time[i]=element;
        printf("Priority of process %d: ", i+1);
        scanf("%d", &priority[i]);
    }

    sort_arr(process_id_arr, arr_time, burst_time, temp_b_time, priority, total_process);

    int completion_time[SIZE], waiting_time[SIZE], turn_arnd_time[SIZE];

    //adding the first available process into in_queue array
    process_id.enqueue(process_id_arr[0], &process_id);
    in_queue[in_queue_len++] = process_id_arr[0];

    int total = total_process;

    while(total!=0)
    {
        int temp=0;
        //sorting the current available process according to their priority
        for(i=0; i<in_queue_len-1; i++)
        {
            for(j=start; j<in_queue_len-1-i; j++)
            {
                index  = index_id(in_queue[j], process_id_arr, total_process);
                index1 = index_id(in_queue[j+1], process_id_arr, total_process);

                if(priority[index]<priority[index1])
                {
                    swap(&in_queue[j], &in_queue[j+1]);
                }
            }
        }

        /*for(i=0; i<in_queue_len; i++)
        {
            printf("%d ", in_queue[i]);
        }
        printf("\n");*/

        //getting top element out of not completed one
        /*if(start+2==in_queue_len)
        {
            index  = index_id(in_queue[start], process_id_arr, total_process);
            index1 = index_id(in_queue[start+1], process_id_arr, total_process);

            if(priority[index]<priority[index1])
            {
                swap(&in_queue[start], &in_queue[start+1]);
            }
        }*/
        element = in_queue[start];
        index = index_id(element, process_id_arr, total_process);

        if(c_time==0)
        {
            c_time = arr_time[index];
        }

        if(temp_b_time[index]>1)
        {
            temp_b_time[index] = temp_b_time[index]-1;
            c_time++;
            temp=1;
        }
        else if(temp_b_time[index]==1)
        {
            temp_b_time[index] = temp_b_time[index]-1;
            c_time++;
            start++;
            completion_time[index] = c_time;
            total--;
            temp=1;
        }

        //if cpu is in idle state
        if(temp==0)
        {
            c_time++;
        }

        for(i=0; i<total_process; i++)
        {
            if(arr_time[i]<=c_time && !(pre(in_queue, in_queue_len, process_id_arr[i])))
            {
                in_queue[in_queue_len++]=process_id_arr[i];
            }
        }
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

    printf("Processes   arrival_time   Burst time      priority  completion time   Turn around time   Waiting time\n");
    for(i=0; i<total_process; i++)
    {
        printf("%d", process_id_arr[i]);
        printf("\t \t %d", arr_time[i]);
        printf("\t \t %d", burst_time[i]);
        printf("\t \t %d", priority[i]);
        printf("\t \t %d", completion_time[i]);
        printf("\t \t %d", turn_arnd_time[i]);
        printf("\t \t %d \n", waiting_time[i]);
    }
    float avg_wait = tot_waiting_time/total_process;
    float avg_trt = tot_trt/total_process;
    printf("Average waiting time is : %f\n", avg_wait);
    printf("Average turn around time is: %f", avg_trt);


}
