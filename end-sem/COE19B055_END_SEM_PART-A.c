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
    int process_id_arr[100], arr_time[100], burst_time[100], temp_b_time[100], in_queue[100], in_queue_len=0, time_q, c_time=0, element, index;
    float tot_waiting_time_rr=0, tot_trt_rr=0;

    printf("Enter no of process: ");
    scanf("%d", &total_process);

    /*printf("Enter time quantum: ");
    scanf("%d", &time_q);*/
    time_q = 2;
    
    for(i=0; i<total_process; i++)
    {
    	printf("Enter Process_id, Arrival tim and Burst time of process %d:(seperated by space) ", i+1);
    	scanf("%d %d %d", &process_id_arr[i], &arr_time[i], &element);
    	burst_time[i]=element;
        temp_b_time[i]=element;
    }
    
	//Round Robbin
    sort_arr(process_id_arr, arr_time, burst_time, temp_b_time, total_process);

    int completion_time_rr[100], waiting_time_rr[100], turn_arnd_time_rr[100];

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
            else
            {
                c_time = c_time + temp_b_time[index];
                temp_b_time[index] = 0;
                completion_time_rr[index] = c_time;
                //printf("%d - %d\n", index, completion_time[index]);
                total--;
                temp_1=1;
            }

            //enqueue the process arrived by the current c_time
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

    for(i=0; i<total_process; i++)
    {
        turn_arnd_time_rr[i] = completion_time_rr[i] - arr_time[i];
        tot_trt_rr = tot_trt_rr + turn_arnd_time_rr[i];
    }

    for(i=0; i<total_process; i++)
    {
        waiting_time_rr[i] = turn_arnd_time_rr[i] - burst_time[i];
        tot_waiting_time_rr = tot_waiting_time_rr + waiting_time_rr[i];
    }

	printf("Round Robbin\n");
    printf("Processes   arrival_time   Burst time  completion time   Turn around time   Waiting time\n");
    for(i=0; i<total_process; i++)
    {
        printf("%d", process_id_arr[i]);
        printf("\t \t %d", arr_time[i]);
        printf("\t \t %d", burst_time[i]);
        printf("\t \t %d", completion_time_rr[i]);
        printf("\t \t %d", turn_arnd_time_rr[i]);
        printf("\t \t %d \n", waiting_time_rr[i]);
    }
    float avg_wait_rr = tot_waiting_time_rr/total_process;
    float avg_trt_rr = tot_trt_rr/total_process;
    printf("Average waiting time is : %f\n", avg_wait_rr);
    printf("Average turn around time is: %f\n", avg_trt_rr);

    //Round Robin end



	//HRRN
			
	int completion_time_hrrn[100], waiting_time_hrrn[100], turn_arnd_time_hrrn[100], completed[100];
	float tot_waiting_time_hrrn=0, tot_trt_hrrn=0, response_ratio, temp;
	
	for(i=0; i<total_process; i++)
	{
		response_ratio = -999;
		c_time= ((i==0 || c_time<arr_time[i]) ? arr_time[i] : c_time);

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
		
		completion_time_hrrn[index]=c_time;
	}
	
	for(i=0; i<total_process; i++)
    {
        turn_arnd_time_hrrn[i] = completion_time_hrrn[i] - arr_time[i];
        tot_trt_hrrn = tot_trt_hrrn + turn_arnd_time_hrrn[i];
    }

    for(i=0; i<total_process; i++)
    {
        waiting_time_hrrn[i] = turn_arnd_time_hrrn[i] - burst_time[i];
        tot_waiting_time_hrrn = tot_waiting_time_hrrn + waiting_time_hrrn[i];
    }
	
	printf("HRRN\n");
	printf("Processes   arrival_time   Burst time  completion time   Turn around time   Waiting time\n");
    for(i=0; i<total_process; i++)
    {
        printf("%d", process_id_arr[i]);
        printf("\t \t %d", arr_time[i]);
        printf("\t \t %d", burst_time[i]);
        printf("\t \t %d", completion_time_hrrn[i]);
        printf("\t \t %d", turn_arnd_time_hrrn[i]);
        printf("\t \t %d \n", waiting_time_hrrn[i]);
    }
    
    float avg_wait_hrrn = tot_waiting_time_hrrn/total_process;
    float avg_trt_hrrn = tot_trt_hrrn/total_process;
    printf("Average waiting time is : %f\n", avg_wait_hrrn);
    printf("Average turn around time is: %f\n", avg_trt_hrrn);
    
    if(avg_wait_rr > avg_wait_hrrn)
    {
    	printf("HRRN has less waiting time for given set of process\n");
    }
    else if(avg_wait_hrrn > avg_wait_rr)
    {
    	printf("RR has less waiting time for given set of process\n");
    }
    else
    {
    	printf("Both RR and HRRN has same waiting time for given set of process\n");
    }
    
    if(avg_trt_rr > avg_trt_hrrn)
    {
    	printf("HRRN has less turn around time for given set of process\n");
    }
    else if(avg_trt_hrrn > avg_trt_rr)
    {
    	printf("RR has less turn around time for given set of process\n");
    }
    else
    {
    	printf("Both RR and HRRN has same turn around time for given set of process\n");
    }
}


