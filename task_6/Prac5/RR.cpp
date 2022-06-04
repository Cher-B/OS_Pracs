#include<iostream>
#include <algorithm> 
using namespace std;

#define MAX 3

struct p{
    int process_id;
    int burst_time;
    int arrival_time;
};
int waitTime[MAX];
int turnAroundTime[MAX];
int temp[MAX];

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
void printAll(p processes[],int turnAroundTime[],int waitTime[],int temp[]){
    cout<<"Process ID   "<<"Arrival Time  "<<"Burst Time   "<<"Waiting Time   "<<"Turn Around Time"<<endl;
    for(int i = 0;i<MAX;i++){
        cout<<processes[i].process_id<<"\t\t"<<processes[i].arrival_time<<"\t\t"<<temp[i]<<"\t\t"<<waitTime[i]<<"\t\t"<<turnAroundTime[i]<<endl;
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
    struct p processes[MAX];
    struct p currentProcess;
    int smallest,count = 0,end,quantum;
    float total_wt = 0,total_tat = 0;
    cout<<"Enter Quantum:";
    cin>>quantum;

    for(int i = 0;i<MAX;i++){
        cout<<"Enter Process ID:"<<i+1<<endl;
        processes[i].process_id = i+1;
        cout<<"Enter Arrival Time:0"<<endl;
        processes[i].arrival_time=0;
        cout<<"Enter Burst Time:";
        cin>>processes[i].burst_time;
        temp[i] = processes[i].burst_time;
    }
    int t = 0;
    while(count!=MAX){
        bool done = true;
        for(int i = 0;i<MAX;i++){
            if(processes[i].burst_time>0){
                done = false;
                if(processes[i].burst_time>quantum){
               t = t + quantum;
               processes[i].burst_time -= quantum;
           }else{
               t = t + processes[i].burst_time;
               turnAroundTime[i] = t;
               waitTime[i] = t - temp[i];
               processes[i].burst_time=0;               
               count++;
                }
            }
            if(done == true){
                break;
            }
           
        }

    }

    printAll(processes,turnAroundTime,waitTime,temp);

    cout<<"Average Turn Around Time: "<<findAvgTurnAroundTime(turnAroundTime)<<endl;
    cout<<"Average Wait Time: "<<findAvgWaitTime(waitTime)<<endl;
    
    return 0;
}