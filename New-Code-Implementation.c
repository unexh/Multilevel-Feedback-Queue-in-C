#include<stdio.h>
#include<stdlib.h>//for malloc and calloc

//defining a structure of a process
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

//Input func : that takes processes from user
void takeInputProcess(int count,PD* process){
    for(int i=0;i<count;i++){
        printf("Enter Pid, ArrivalTime, BurstTime and PriorityNumber for Process[%d] : ",i+1);
		scanf("%d %d %d %d",&process[i].Pid,&process[i].ArrivalTime,&process[i].BurstTime,&process[i].Priority);
        //take input
    }
    //printing for testing input just taken
    printf("\n\nPrinting info Entered:\n");
    for(int i=0;i<count;i++){
        printf("Process[%d], Pid:%d, ArrivalTime:%d,BurstTime:%d,PriorityNumber:%d\n",i+1,process[i].Pid,process[i].ArrivalTime,process[i].BurstTime,process[i].Priority);
    }
}


int main(){
    int processCount=0;
    printf("Enter the total number of process : ");
    scanf("%d",&processCount);
    //test
    //printf("Total number Entered : %d",processCount);
    PD *process;
    process = (PD*) calloc(processCount,sizeof(PD));
    if(process == NULL){
        printf("Sorry No allocation is possible Right Now!");
    }
    takeInputProcess(processCount,process);

}
