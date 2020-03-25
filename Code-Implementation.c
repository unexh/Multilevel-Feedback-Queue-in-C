#include<unistd.h>
#include<stdio.h>
#include<stdbool.h>

struct Process{
	int Number;
	int Pid;
	int BrustTime;
	int Priority;
	int ArrivalTime;
	int Finishtime;
	int RemainTime;
	int StartTime;
	int WaitTime;
	int ResTime;
}CurrentProcess;

typedef struct Process PD;

//id-vise sorting
bool PidSort(PD* a ,PD* b){
	return (*a).Pid<(*b).Pid;
}
//Sorting elements in order of Arrival time
//,Priority and Pid

bool SortingArrival(const PD* a,const PD* b){
	if((*a).ArrivalTime<(*b).ArrivalTime){
		return true;}
	else {
		return false;}

	if((*a).Priority<(*b).Priority){
		return true;}
	else{
		return false;}

	if((*a).Pid<(*b).Pid)
		return true;

	return false;
}

bool NumSort(const PD* a, const PD* b){
	return (*a).Number<(*b).Number;
	}
//sorting in order of Priority and then P id

struct Compare{
	bool operator()(PD* a,PD* b){
		if((*a).Priority > (*b).Priority){
			return true;}
		else{
			return false;}

		if((*a).Pid > (*b).Pid){
			return true;}

		return false;
	}
};

//to check the input
void Check(vector<PD> inparr){
	for(int i=0;i<inparr.size();i++){
		printf("Pid : %d | Arrival Time : %d | Burst Time : %d | Priority : %d\n",mv[i].Pid,mv[i].ArrivalTime,mv[i].BrustTime,mv[i].Priority);
		}
}

int main(){
	printf("Testing");

	vector<PD> input;
	vector<PD> inputCopy;
	PD tempHold;
	int FqProcess=0 , SqProcess=0 , ArrivalTime,BurstTime,Pid,N,Priority,TProcessCount,Clock, TET = 0;//TET: totalExecutionTime
	printf("Enter The total number of process : ");
	scanf("%d",N);

	for(int i=0;i<TProcessCount;i++){
		printf("Enter Pid, ArrivalTime, BurstTime and PriorityNumber for Process[%d]",i+1);
		scanf("%d %d %d %d",&Pid,&ArrivalTime,&BurstTime,&Priority);

	}
}
