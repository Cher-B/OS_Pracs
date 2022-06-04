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

bool compare(p p1,p p2){
    return p1.arrival_time<p2.arrival_time;
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
    cout<<"Process ID  "<<"Arrival Time "<<"Burst Time  "<<"Waiting Time  "<<"Turn Around Time"<<endl;
    for(int i = 0;i<MAX;i++){
        cout<<processes[i].process_id<<"\t\t"<<processes[i].arrival_time<<"\t\t"<<processes[i].burst_time<<"\t\t"<<waitTime[i]<<"\t\t"<<turnAroundTime[i]<<endl;
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
    int smallest,count = 0,end;
    float total_wt = 0,total_tat = 0;

    for(int i = 0;i<MAX;i++){
        cout<<"Enter Process ID:"<<i+1<<endl;
        processes[i].process_id = i+1;
        cout<<"Enter Arrival Time:";
        cin>>processes[i].arrival_time;
        cout<<"Enter Burst Time:";
        cin>>processes[i].burst_time;
        temp[i] = processes[i].burst_time;
    }

    // sort(processes,processes+MAX,compare);

    // findWaitingTime(processes,waitTime);
    // findTurnAroundTime(processes,waitTime,turnAroundTime);
    // printAll(processes,turnAroundTime,waitTime);

    // cout<<"Average Turn Around Time: "<<findAvgTurnAroundTime(turnAroundTime)<<endl;
    // cout<<"Average Wait Time: "<<findAvgWaitTime(waitTime)<<endl;

    // while(counterComplete != MAX){
    //     sort(processes,processes+MAX,compare);//sort wrt to burst time

    //     currentProcess = processes[0];//select current shorted process

    //     cout<<"Process ID:"<<currentProcess.process_id<<endl;
    //     cout<<"Burst Time:"<<currentProcess.burst_time<<endl;
        
    //     if(currentProcess.burst_time == 0){
    //         counterComplete++;
    //         continue;
    //     }
    //     processes[0].burst_time -= 1;//reduce burst time of current process by 1

    // }

    // processes[9].burst_time = 9999;
    // for(int t = 0;count!=MAX;t++){
    //     smallest = 9;
    //     for(int i = 0;i<MAX;i++){
    //         if(processes[i].arrival_time <= t && processes[i].burst_time<processes[smallest].burst_time && processes[i].burst_time>0){
    //             smallest = i;
    //         }
    //     }
    //     cout<<processes[smallest].process_id<<","<<processes[smallest].burst_time<<","<<count<<","<<t<<endl;
    //     processes[smallest].burst_time--;
    //     if(processes[smallest].burst_time == 0){
    //         count++;
    //         end = t+1;
    //         total_wt = total_wt + end - processes[smallest].arrival_time - temp[smallest];
    //         total_tat = total_tat + end - processes[smallest].arrival_time;
    //     }
    // }
    // cout<<"Average Wait Time:"<<total_wt/MAX<<endl;
    // cout<<"Average Turn Around Time:"<<total_tat/MAX<<endl;

    // processes[9].burst_time = 9999999;
    for(int t=0;count!=MAX;t++){
        smallest = -1;
        for(int i = 0;i<MAX;i++){
            if(processes[i].arrival_time <= t){
                if(processes[i].burst_time<processes[smallest].burst_time){
                    if(processes[i].burst_time>0){
                        smallest = i;
                    }
                }
            }
        }
        processes[smallest].burst_time--;
        
        cout<<processes[smallest].process_id<<","<<processes[smallest].burst_time<<","<<count<<","<<t<<endl;
        if(t==200){
            break;
        }
        
        if(processes[smallest].burst_time == 0){
            for(int i = 0;i<MAX;i++){
                cout<<processes[i].burst_time<<"\t";
            }
            cout<<endl;
        }
        if(processes[smallest].burst_time == 0){
            count++;
            end = t+1;
            total_wt = total_wt + end - processes[smallest].arrival_time - temp[smallest];
            total_tat = total_tat + end - processes[smallest].arrival_time;
        }
    }
    cout<<"Average Wait Time:"<<total_wt/MAX<<endl;
    cout<<"Average Turn Around Time:"<<total_tat/MAX<<endl;
    
    return 0;
}