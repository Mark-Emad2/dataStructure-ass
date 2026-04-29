#include <bits/stdc++.h>

using namespace std;



struct  Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool isComplete;
    bool inQueue;

};
 // class work{
 // private:
 //
 //     queue<int>p;
 //     queue<Process>data;
 //     int timeQuantum;
 //     int currentTime;
 //
 // public:
 //     work(queue<int>p, deque<Process>data, int time, int current) {
 //         p=p;
 //         data=data;
 //         timeQuantum=time;
 //         currentTime=current;
 //     }
 //     void addProcess(int id, int arrival, int burst) {
 //         data.push(Process(id,arrival,burst));
 //     }
 //
 // };

void checkForArrival(Process processes[], int NumberProcess,int currentTime,queue<int> &readyQueue) {
    for (int i =0;i < NumberProcess;i++) {
        if (processes[i].arrival_time<=currentTime and !processes[i].inQueue and !processes[i].isComplete) {
            processes[i].inQueue=true;
            readyQueue.push(i);
        }
    }
}

void printQueueState(queue<int> &readyQueue, Process processes[])
{
    cout << "[ ";
    queue<int> temp = readyQueue;
    while (!temp.empty())
    {
        cout << "P" << processes[temp.front()].id << " ";
        temp.pop();
    }
    cout << "]" << endl;
}

void updateQueue(Process processes[], int NumberProcess, int timeQuantum, queue<int> &ready_queue, int &currentTime, int &programsExecuted) {
    int x=ready_queue.front();
    ready_queue.pop();

    if (processes[x].remaining_time <= timeQuantum) {
        processes[x].isComplete=true;
        currentTime+=processes[x].remaining_time;
        processes[x].completion_time = currentTime;
        processes[x].waiting_time=processes[x].completion_time-processes[x].arrival_time-processes[x].burst_time;
        processes[x].turnaround_time=processes[x].waiting_time+processes[x].burst_time;

        if (processes[x].waiting_time < 0)
            processes[x].waiting_time = 0;

        programsExecuted++;

        if (programsExecuted != NumberProcess)
        {
            checkForArrival(processes, NumberProcess, currentTime, ready_queue);
        }
    }else {
        processes[x].remaining_time -= timeQuantum;
        currentTime += timeQuantum;

        if (programsExecuted != NumberProcess) {
            checkForArrival(processes, NumberProcess, currentTime, ready_queue);
        }

        ready_queue.push(x);
    }
}

void output(Process processes[],int NumberProcess) {
    double avgWaitingTime=0;

    sort(processes, processes + NumberProcess, [](const Process &p1, const Process &p2)
         { return p1.id < p2.id; });

    cout << "\nProcess Completion Time, Turnaround Time, Waiting Time" << endl;
    for (int i=0;i<NumberProcess;i++) {
        cout << "P" << processes[i].id << " "
             << processes[i].completion_time << " "
             << processes[i].turnaround_time << " "
             << processes[i].waiting_time << endl;
        avgWaitingTime += processes[i].waiting_time;
    }
    cout << "Average Waiting Time: " << (double)avgWaitingTime / NumberProcess << endl;
}

void roundRobin(Process processes[], int NUmberProcesses, int timeQuantum) {
    queue<int> readyQueue;
    int currentTime = 0;
    int programsExecuted = 0;

    checkForArrival(processes, NUmberProcesses, currentTime, readyQueue);

    while (programsExecuted < NUmberProcesses) {
        if (readyQueue.empty()) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < NUmberProcesses; i++) {
                if (!processes[i].isComplete && processes[i].arrival_time < nextArrival) {
                    nextArrival = processes[i].arrival_time;
                }
            }
            currentTime = nextArrival;
            checkForArrival(processes, NUmberProcesses, currentTime, readyQueue);
            continue;
        }

        printQueueState(readyQueue, processes);
        updateQueue(processes, NUmberProcesses, timeQuantum, readyQueue, currentTime, programsExecuted);
    }

    cout << "[ Empty ]" << endl;
}

int main(){
    int NumberProcess,timeQuantum;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;
    cout << "the number of processes: ";
    cin >> NumberProcess;

    Process processes[NumberProcess + 1];

    for (int i = 0; i < NumberProcess; i++)
    {
        cout << "Enter arrival time and burst time of p" << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].id = i + 1;
        cout << endl;
    }


    sort(processes, processes + NumberProcess, [](const Process &p1, const Process &p2)
         { return p1.arrival_time < p2.arrival_time; });

    roundRobin(processes, NumberProcess, timeQuantum);

    output(processes, NumberProcess);

    return 0;

}