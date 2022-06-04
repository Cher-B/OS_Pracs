#include<iostream>
#include <algorithm> 
using namespace std;

#define MAX 7

struct p{
    int process_id;
    int burst_time;
    int arrival_time;
    int priority;
};
int waitTime[MAX];
int turnAroundTime[MAX];

bool compare(p p1,p p2){
    if(p1.arrival_time<p2.arrival_time){
        return true;
    }else if(p1.arrival_time == p2.arrival_time){
        if (p1.priority<p2.priority){
            return true;
        }else if(p1.priority == p2.priority){
            return (p1.process_id<p2.process_id);
        }else{
            return false;
        }
    }  
    else{
        return false;
    }    
}
void findWaitingTime(p processes[],int waitTime[]){
    waitTime[0] = 0;
    for(int i=1;i<MAX;i++){
        waitTime[i] = processes[i-1].burst_time + waitTime[i-1];
    }
}
void findTurnAroundTime(p processes[],int waitTime[],int turnAroundTime[]){
    for(int i = 0;i<MAX;i++){
        turnAroundTime[i] = processes[i].burst_time + waitTime[i];
    }
}
void printAll(p processes[],int turnAroundTime[],int waitTime[]){
    cout<<"Process ID  "<<"Arrival Time "<<"Priority  "<<"Burst Time  "<<"Waiting Time  "<<"Turn Around Time"<<endl;
    for(int i = 0;i<MAX;i++){
        cout<<processes[i].process_id<<"\t\t"<<processes[i].arrival_time<<"\t\t"<<processes[i].priority<<"\t\t"<<processes[i].burst_time<<"\t\t"<<waitTime[i]<<"\t\t"<<turnAroundTime[i]<<endl;
    }
}
float findAvgTurnAroundTime(int turnAroundTime[]){
    float total_tat = 0;
    float avg;
    for(int i = 0;i<MAX;i++){
        total_tat += turnAroundTime[i];
    }
    avg = total_tat/MAX;
    return avg;
}
float findAvgWaitTime(int waitTime[]){
    float total_wt = 0;
    float avg;
    for(int i= 0;i<MAX;i++){
        total_wt += waitTime[i];
    }
    avg = total_wt/MAX;
    return avg;
}

int main(){
    p processes[MAX];

    

    for(int i = 0;i<MAX;i++){
        cout<<"Enter Process ID:"<<i+1<<endl;
        processes[i].process_id = i+1;
        cout<<"Enter Process Priority:";
        cin>>processes[i].priority;
        cout<<"Enter Arrival Time:";
        cin>>processes[i].arrival_time;
        cout<<"Enter Burst Time:";
        cin>>processes[i].burst_time;
        
    }

    sort(processes,processes+MAX,compare);

    findWaitingTime(processes,waitTime);
    findTurnAroundTime(processes,waitTime,turnAroundTime);
    printAll(processes,turnAroundTime,waitTime);

    cout<<"Average Turn Around Time: "<<findAvgTurnAroundTime(turnAroundTime)<<endl;
    cout<<"Average Wait Time: "<<findAvgWaitTime(waitTime)<<endl;

    return 0;
}