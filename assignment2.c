#include<stdio.h>
#include<stdlib.h>

struct Process
{
    int id;
    int arrivel_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
};

void printProcess(struct Process processes[],int n){
    printf("\nid\t arrivel_time\t burst_time\t remaining_time\t ta_time\t waiting_time");
    for (int i = 0; i < n; i++)
    {
        printf("\nP%d \t %d \t\t %d \t\t %d \t\t %d \t\t %d",processes[i].id,processes[i].arrivel_time,processes[i].burst_time,processes[i].remaining_time,processes[i].turnaround_time,processes[i].waiting_time);
    }
}

void shortestJobFirst(struct Process processes[],int n){
    int current_time=0;
    int completed=0;
    int shortest = -1;
    float atat = 0.0,awt=0.0;

    printf("\nShortest Job First(Preemtive)");
    printf("\nGantt Chart:\n");

    while (completed<n) 
    {
        shortest = -1;

        //find Shortest job based on remaing time
        for (int i = 0; i < n; i++)
        {
            if(processes[i].arrivel_time<=current_time && processes[i].remaining_time>0){
                if (shortest ==-1|| processes[i].remaining_time<processes[shortest].remaining_time)
                {
                    shortest=i;
                }
                
            }
        }
        

        //check no process arrive at current time
        if(shortest ==-1){
            current_time++;
        }
        else{
            printf("P%d |",processes[shortest].id);
            processes[shortest].remaining_time--;
            current_time++;

            //check if process completed or not

            if (processes[shortest].remaining_time ==0)
            {
                completed++;
                processes[shortest].turnaround_time = current_time - processes[shortest].arrivel_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time-processes[shortest].burst_time;
            }
        }
    }
    printf("\n");
    printProcess(processes,n);
    for (int i = 0; i < n; i++)
    {
        atat += processes[i].turnaround_time;
        awt += processes[i].waiting_time;
    }

    atat = atat/(float)n;
    awt = awt/(float)n;
    
    printf("\nAvarage Turn Around time : %f\nAvarage Waiting time : %f",atat,awt);

}

void roundRobin(struct Process processes[],int n){
    int current_time=0;
    int completed=0;
    int time_quantum;
    float atat = 0.0,awt=0.0;

    printf("\nEnter time Quantum : ");
    scanf("%d",&time_quantum);

    while (completed<n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivel_time<=current_time && processes[i].remaining_time>0)
            {
                printf("|P%d\t",processes[i].id);

                //check if process remaining time is less than time quantum;
            
                if(processes[i].remaining_time<=time_quantum){
                    current_time+=processes[i].remaining_time;
                    processes[i].remaining_time =0;
                    completed++;

                    processes[i].turnaround_time = current_time - processes[i].arrivel_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                }
                else{
                    current_time +=time_quantum;
                    processes[i].remaining_time -=time_quantum;
                }
            }
            
        }
        
    }
    printf("\n");
    printProcess(processes,n);
    for (int i = 0; i < n; i++)
    {
        atat += processes[i].turnaround_time;
        awt += processes[i].waiting_time;
    }

    atat = atat/(float)n;
    awt = awt/(float)n;
    
    printf("\nAvarage Turn Around time : %f\nAvarage Waiting time : %f",atat,awt);
    
}

int main(int argc, char const *argv[])
{
    int n;
    printf("\nEnter the No. of process : ");
    scanf("%d",&n);
    struct Process processes[n],temp;

    for (int i = 0; i < n; i++)
    {
        processes[i].id=i;
        printf("\nEnter Process P%d Arrival Time and Burst Time : ",i);
        scanf("%d %d", &processes[i].arrivel_time,&processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    //Sort the process based on arrival time

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if(processes[j].arrivel_time>processes[j+1].arrivel_time){
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1]=temp;
            }
        }
    }

    roundRobin(processes,n);
    
    printf("\n\n");
    return 0;
}
