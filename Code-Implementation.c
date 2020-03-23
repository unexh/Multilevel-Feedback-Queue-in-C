#include<unistd.h>

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
}

struct Process CurrentProcess;
typedef struct Process PD;

//id-vise sorting
bool PidSort(const PD& a , const PD& b){
    return a.Pid<b.Pid;
}

//Sorting elements in order of Arrival time
//,Priority and Pid

bool SortingArrival(const PD& a,const PD& b){
    if(a.ArrivalTime<b.ArrivalTime){
        return true;}
    else {
        return false;}

    if(a.Priority<y.Priority){
        return true;}
    else{
        return false;}

    if(a.Pid<b.Pid)
        return true;

    return false;
}

bool NumSort(const PD& a, const PD& b){
    return a.Number<b.Number;
    }
//sorting in order of Priority and then Pid

struct Compare{
    bool operator()(const PD& a,const PD& y){
        if(a.Priority > b.Priority){
            return true;}
        else{
            return false;}

        if(a.Pid > y.Pid){
            return true;}

        return false;
    }
}

//to check the input
void Check(vector<PD> inparr){
    for(int i=0;i<inparr.size();i++){
        printf("Pid : %d | Arrival Time : %d | Burst Time : %d | Priority : %d\n",mv[i].Pid,mv[i].ArrivalTime,mv[i].BrustTime,mv[i].Priority);
        }
}

int main(){
    printf("Testing");
}
