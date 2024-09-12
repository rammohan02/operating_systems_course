#define size 100
struct queue
{
    int front,rear;
    int array[size];
    void (*enqueue)(int ,struct queue* );
    void (*dequeue)(struct queue* );
    void (*display)(struct queue* );
    int (*empty) (struct queue* );
};
void enqueue1(int ,struct queue* );
void dequeue1(struct queue* );
void display1(struct queue* );
void enqueue1(int item,struct queue *que)
{
    if((que->rear==size-1 && que->front==0) || (que->front==que->rear+1))
    {
        printf("queue is full\n");
    }
    else
    {
        if(que->front==-1)
        {
            que->front=0;
        }
        que->rear=(que->rear+1)%size;
        que->array[que->rear]=item;
    }
}
void dequeue1(struct queue *que)
{
    if(que->front==-1)
    {
        printf("queue is empty\n");
    }
    else
    {
        if(que->front==que->rear)
        {
            que->rear=-1;
            que->front=-1;
        }
        else
        {
            que->front=(que->front+1)%size;
        }
    }
}
void display1(struct queue *que)
{
    int i;
    if(que->rear==-1 && que->front==-1)
    {
        printf("The queue is empty\n");
    }
    else
    {
        if(que->front < que->rear)
        {
            for(i=que->front;i<=que->rear;i++)
            {
                printf("%d ",que->array[i]);
            }
        }
        else if(que->front == que->rear)
        {
            printf("%d ",que->array[que->front]);
        }
        else
        {
            for(i=que->front;i<size;i++)
            {
                printf("%d ",que->array[i]);
            }
            for(i=0;i<=que->rear;i++)
            {
                printf("%d ",que->array[i]);
            }
        }
        printf("\n");
    }
}

int empty1(struct queue *que)
{
    if(que->front==-1)
    {
        return 1;
    }
    return 0;
}

