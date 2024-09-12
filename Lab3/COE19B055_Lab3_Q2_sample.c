//COE19B055
//K. Ram Mohan
#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

void swap(int *p,int *q)
{
    int temp;
    temp=*p;
    *p=*q;
    *q=temp;
}

//function to sort based on arrival time
void sort_arr(int id[], int arr[], int burst_time[], int temp_b_time[], int len)
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
                    swap(&temp_b_time[j], &temp_b_time[j+1]);
                    go=1;
                }

                if(arr[j]==arr[j+1])
                {
                    if(id[j]>id[j+1])
                    {
                        swap(&arr[j], &arr[j+1]);
                        swap(&id[j], &id[j+1]);
                        swap(&burst_time[j], &burst_time[j+1]);
                        swap(&temp_b_time[j], &temp_b_time[j+1]);
                        go=1;
                    }
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
    int process_id_arr[100], arr_time[100], burst_time[100], temp_b_time[100], in_queue[100], in_queue_len=0, time_q, c_time=0, low_bt, var, element, index;
    float tot_waiting_time=0, tot_trt=0;

    printf("Enter no of process: ");
    scanf("%d", &total_process);

    printf("Enter time quantum: ");
    scanf("%d", &time_q);

    for(i=0; i<total_process; i++)
    {
        printf("Process_id of process %d: ", i+1);
        scanf("%d", &process_id_arr[i]);
        //scanf("%d", &element);
        //process_id_arr[i] = element;
        //process_id.enqueue(element, &process_id);
        printf("Arrival time of process %d: ", i+1);
        scanf("%d", &arr_time[i]);
        printf("Burst time of process %d: ", i+1);
        scanf("%d", &element);
        burst_time[i]=element;
        temp_b_time[i]=element;
    }

    sort_arr(process_id_arr, arr_time, burst_time, temp_b_time, total_process);

    int completion_time[100], waiting_time[100], turn_arnd_time[100];

    /*for(i=0; i<total_process; i++)
    {
        process_id.enqueue(process_id_arr[i], &process_id);
    }*/

    //adding the first available process into queue
    process_id.enqueue(process_id_arr[0], &process_id);
    in_queue[in_queue_len++] = process_id_arr[0];

    i=0;
    int total=total_process;
    while(!(process_id.empty(&process_id)) || total!=0)
    {
        //There are process that did not come to queue which means their arrival time is more than current c_time
        if(process_id.empty(&process_id))
        {
            c_time++;

            for(i=0; i<total_process; i++)
            {
                if(arr_time[i]<=c_time && !(pre(in_queue, in_queue_len, process_id_arr[i])))
                {
                    in_queue[in_queue_len++] = process_id_arr[i];
                    process_id.enqueue(process_id_arr[i], &process_id);
                }
            }
        }
        else
        {
            int temp=0, temp_1=0;
            //getting the process id to be executed
            element = process_id.array[process_id.front];
            //getting the index of the process id
            index = index_id(element, process_id_arr, total_process);
            //printf("%d - a\n", index);
            //dequeuing the process for execution
            process_id.dequeue(&process_id);

            //if it is the first process available or if arr_time is more than c_time
            if(c_time==0 || arr_time[index]>c_time)
            {
                c_time = arr_time[index];
            }

            //if burst time is more than time slice
            if(temp_b_time[index]>time_q)
            {
                temp_b_time[index] = temp_b_time[index]-time_q;
                c_time = c_time + time_q;
                temp=1;
                temp_1=1;
            }
            else if(temp_b_time[index]==time_q)
            {
                temp_b_time[index] = 0;
                c_time = c_time + time_q;
                completion_time[index] = c_time;
                //printf("%d - %d\n", index, completion_time[index]);
                total--;
                temp_1=1;
            }
            else
            {
                c_time = c_time + temp_b_time[index];
                temp_b_time[index] = 0;
                completion_time[index] = c_time;
                //printf("%d - %d\n", index, completion_time[index]);
                total--;
                temp_1=1;
            }

            for(i=0; i<total_process; i++)
            {
                if(arr_time[i]<=c_time && !(pre(in_queue, in_queue_len, process_id_arr[i])))
                {
                    in_queue[in_queue_len++] = process_id_arr[i];
                    process_id.enqueue(process_id_arr[i], &process_id);
                }
            }

            if(temp==1)
            {
                process_id.enqueue(element, &process_id);
            }
        }
        //printf("%d - ", c_time);
        //process_id.display(&process_id);

    }

    /*while(!(process_id.empty(&process_id)))
    {
        if(process_id.front!=-1)
        {
            element = process_id.array[process_id.front];
            index = index_id(element, process_id_arr, total_process);
            //printf("%d - a\n", index);
            process_id.dequeue(&process_id);
            if(c_time==0 || arr_time[index]>c_time)
            {
                c_time = arr_time[index];
            }

            if(temp_b_time[index]>time_q)
            {
                temp_b_time[index] = temp_b_time[index]-time_q;
                c_time = c_time + time_q;
                process_id.enqueue(element, &process_id);
            }
            else if(temp_b_time[index]==time_q)
            {
                temp_b_time[index] = 0;
                c_time = c_time + time_q;
                completion_time[index] = c_time;
            }
            else
            {
                c_time = c_time + temp_b_time[index];
                temp_b_time[index] = 0;
                completion_time[index] = c_time;
            }
        }
        /*else
        {
            element = process_id.array[process_id.front];
            index = index_id(element, process_id_arr, total_process);
            //printf("%d - b\n", index);
            process_id.dequeue(&process_id);

            if(c_time==0 || arr_time[index]>c_time)
            {
                c_time = arr_time[index];
            }


        }
    }*/

    for(i=0; i<total_process; i++)
    {
        printf("%d \n", completion_time[i]);
    }

}

