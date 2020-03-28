#include<stdio.h>
#include<stdlib.h>//for malloc and calloc
#include<stdbool.h>
#include<limits.h>

///defining a structure of a process
struct ProcessData{
    int Number;
	int Pid;
	int BurstTime;
	int Priority;
	int ArrivalTime;
	int Finishtime;
	int RemainTime;
	int StartTime;
	int WaitTime;
	int ResTime;
};

typedef struct ProcessData PD;
PD CurrentProcess;

//Input func : that takes processes from user
void takeInputProcess(int count,PD* process){
    for(int i=0;i<count;i++){
        printf("Enter Pid, ArrivalTime, BurstTime and PriorityNumber for Process[%d] : ",i+1);
		scanf("%d %d %d %d",&process[i].Pid,&process[i].ArrivalTime,&process[i].BurstTime,&process[i].Priority);
        //take input
        process[i].Number=i+1;
        process[i].RemainTime = process[i].BurstTime;
    }
}

void printProcessArray(int count,PD* process){
    //printing for testing input just taken
    printf("\n\nPrinting ProcessArray Entered:\n");
    for(int i=0;i<count;i++){
        printf("Process[%d] : Pid:%d | ArrivalTime:%d |BurstTime:%d | PriorityNumber:%d\n",process[i].Number,process[i].Pid,process[i].ArrivalTime,process[i].BurstTime,process[i].Priority);
    }
}

int sortingArrival(const PD* a,const PD* b){
    return (*a).ArrivalTime-(*b).ArrivalTime;
}

bool pidSort(const PD* a , const PD* b){
	return (*a).Pid > (*b).Pid;
}

bool numberSort( const PD* a ,const PD* b){
	return (*a).Number > (*b).Number;
}


///implementing Queue
// A structure to represent a queue
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    PD Data[10];
};


typedef struct Queue NormalQueue;

// function to create a queue of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;  // This is important, see the enqueue
    //queue->Data = (PD*) malloc(queue->capacity * sizeof(PD));
    return queue;
}


// Queue is full when size becomes equal to the capacity
int isFull(struct Queue* queue)
{  return (queue->size == queue->capacity);  }

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{  return (queue->size == 0); }

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, PD prcoessDq )
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->Data[queue->rear]=prcoessDq;
    queue->size = queue->size + 1;
    //printf("Pid [%d], enqueued to queue\n", queue->Data[queue->rear].Pid);
    //printf("enqueued Successfully..\n");
}

//Function to remove an item from queue.
//It changes front and size
void dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    PD dequeuedProcessD = queue->Data[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    //printf("Item Dequeued Successfully\n");
}

//Function to get front of queue
PD front(struct Queue* queue)
{
    if (isEmpty(queue)){
        printf("Empty Queue..\n");
        return;
    }
    return queue->Data[queue->front];
}

//Function to get rear of queue
PD rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return;
    return queue->Data[queue->rear];
}

//////*******************************************************//////

//Priority Queue implementation
typedef struct node {
    PD data;
    // Lower values indicate higher priority
    int priority;
    struct node* next;

} Node;

// Function to Create A New Node
Node* newNode(PD d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
    //printf("First Node added\n");
    return temp;
}

// Return the value at head
PD peek(Node** head)
{
    return (*head)->data;
}

// Removes the element with the
// highest priority form the list
void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

// Function to push according to priority
void push(Node** head, PD d, int p)
{
    //printf("Pushing Next Node\n");
    Node* start = (*head);

    // Create new Node
    Node* temp = newNode(d, p);

    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->priority > p) {

        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
               start->next->priority < p) {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}

// Function to check is list is empty
int isEmptyPQ(Node** head)
{
    return (*head) == NULL;
}



int main(){
    int processCount=0;
    printf("Enter the total number of process : ");
    scanf("%d",&processCount);
    //test
    printf("Total number Entered :[%d]",processCount);
    printf("\n\n");
    PD *process,*processCopy;
    process = (PD*) calloc(processCount,sizeof(PD));
    if(process == NULL){
        printf("Sorry No allocation is possible Right Now!\n");
    }
    //taking input
    takeInputProcess(processCount,process);

    //printing input
    printProcessArray(processCount,process);
    processCopy=process;

    //sorting on the basis of arrival time
    qsort(process,processCount,sizeof(process[0]),sortingArrival);
    //printf("After Qsort (on arrival time) processArray is : \n");
    //printProcessArray(processCount,process);

    int totalExecutionTime = 0;
    totalExecutionTime = totalExecutionTime + process[0].ArrivalTime;

    for(int i=0;i<processCount;i++){
        if(totalExecutionTime>=process[i].ArrivalTime){
            totalExecutionTime = totalExecutionTime + process[i].BurstTime;
        }
        else{
            int difference = (process[i].ArrivalTime - totalExecutionTime);
            totalExecutionTime = totalExecutionTime + difference + process[i].BurstTime;//change
        }
    }

    int Ghant[totalExecutionTime]; //Ghant Chart
    for(int i =0;i<totalExecutionTime;i++){
        Ghant[i]=-1;
    }
    printf("\nTotal Execution Time : [%d]",totalExecutionTime);

    NormalQueue* rQ = createQueue(processCount);//Queue
    Node* pQ = NULL;//PriorityQueue
    int cpuState = 0; //idle if 0 then Idle if 1 the Busy
	int quantum = 4 ; //Time Quantum
	CurrentProcess.Pid = -2;
	CurrentProcess.Priority = 999999;

	int Clock,pQProcesss=0,rQProcesss=0;
	for(Clock=0;Clock<totalExecutionTime;Clock++){
        /**Insert the process with same Arrival time in Priority Queue**/
        for(int i=0;i<processCount;i++){
            if(Clock == process[i].ArrivalTime){
                    if(pQ==NULL){
                        pQ = newNode(process[i],process[i].Priority);
                    }
                    else{
                        push(&pQ,process[i],process[i].Priority);
                    }

            }
        }
        if(cpuState==0){//CPU Idle
            if(!isEmptyPQ(&pQ)){
                CurrentProcess = peek(&pQ);
                cpuState=pQProcesss= 1;
                pop(&pQ);//test POP function
                quantum = 4;
            }
            else if(!isEmpty(rQ)){
                CurrentProcess=front(rQ);
                cpuState=rQProcesss= 1;
                dequeue(rQ);
                quantum=4;
            }
        }
        else if(cpuState==1){ //If CPU has any process
            if(pQProcesss==1 && (!isEmptyPQ(&pQ))){
                if(peek(&pQ).Priority < CurrentProcess.Priority){ //If new process has high priority
                    enqueue(rQ,CurrentProcess); //push CurrentProcess to rQ
                    CurrentProcess = peek(&pQ);
                    pop(&pQ);
                    quantum=4;
                }
            }
            else if(rQProcesss==1 &&(!isEmptyPQ(&pQ))){//If process is from RQ and new process come  in PQ
                enqueue(rQ,CurrentProcess);
                CurrentProcess=peek(&pQ);
                pop(&pQ);
                rQProcesss=0;
                pQProcesss=1;
                quantum=4;
            }

        }
        if(CurrentProcess.Pid != -2){// Process Execution
            CurrentProcess.RemainTime--;
            quantum--;
            Ghant[Clock]=CurrentProcess.Pid;
            if(CurrentProcess.RemainTime == 0){//if process Finishes
                cpuState=0;
                quantum=4;
                CurrentProcess.Pid=-2;
                CurrentProcess.Priority = 999999;
                rQProcesss=pQProcesss=0;

            }
            else if(quantum==0){//If time Quantum of a current running process Finish
                enqueue(rQ,CurrentProcess);
                CurrentProcess.Pid=-2;
                CurrentProcess.Priority=999999;
                rQProcesss=pQProcesss=cpuState=0;
            }
        }
	}

	qsort(process,processCount,sizeof(process[0]),pidSort);

	//print ProcessArray
	/*
	printf("After Qsorting again (pidSort) data :\n");
	printProcessArray(processCount,process);
    */

    for(int i=0;i<processCount;i++){
        for(int j=totalExecutionTime;j>=0;j--){
            if(Ghant[j]==i+1){
                process[i].Finishtime=j+1;
                break;
            }
        }
    }

    for(int i=0;i<processCount;i++){
        for(int j=0;j<totalExecutionTime;j++){
            if(Ghant[j]==i+1){
                process[i].StartTime=j;
                break;
            }
        }
    }

    qsort(process,processCount,sizeof(process[0]),numberSort);
    /*
    //check sorting
    printf("Result after numberSort\n");
    printProcessArray(processCount,process);
    */

    for(int i=0;i<processCount;i++){
        process[i].ResTime=process[i].StartTime-process[i].ArrivalTime;
        process[i].WaitTime=(process[i].Finishtime - process[i].ArrivalTime) - process[i].BurstTime;
    }

    printf("\n\nResult : \n");
    for(int i=0;i<processCount;i++){
        printf("Process[%d] | Pid:[%d] | ResponseTime:[%d]| FinishTime:[%d] | WaitTime:[%d]\n",process[i].Number,process[i].Pid,process[i].ResTime,process[i].Finishtime,process[i].WaitTime);
    }

    return 0;
}
