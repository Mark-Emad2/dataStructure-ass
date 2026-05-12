#include <bits/stdc++.h>
using namespace std;

struct Process {
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

class RoundRobinScheduler {
private:
    Process* processes;
    int numProcesses;
    int timeQuantum;

    void checkForArrival(int currentTime, queue<int> &readyQueue) {
        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrival_time <= currentTime and !processes[i].inQueue and !processes[i].isComplete) {
                processes[i].inQueue = true;
                readyQueue.push(i);
            }
        }
    }

    void printQueueState(queue<int> &readyQueue) {
        cout << "[ ";
        queue<int> temp = readyQueue;
        while (!temp.empty()) {
            cout << "P" << processes[temp.front()].id << " ";
            temp.pop();
        }
        cout << "]" << endl;
    }

    void updateQueue(queue<int> &ready_queue, int &currentTime, int &programsExecuted) {
        int x = ready_queue.front();
        ready_queue.pop();

        if (processes[x].remaining_time <= timeQuantum) {
            processes[x].isComplete = true;
            currentTime += processes[x].remaining_time;
            processes[x].completion_time = currentTime;
            //total time waiting for completion
            processes[x].waiting_time = processes[x].completion_time - processes[x].arrival_time - processes[x].burst_time;
            //total time from arrival to completion
            processes[x].turnaround_time = processes[x].waiting_time + processes[x].burst_time;

            if (processes[x].waiting_time < 0)
                processes[x].waiting_time = 0;

            programsExecuted++;

            if (programsExecuted != numProcesses) {
                checkForArrival(currentTime, ready_queue);
            }
        } else {
            processes[x].remaining_time -= timeQuantum;
            currentTime += timeQuantum;

            if (programsExecuted != numProcesses) {
                checkForArrival(currentTime, ready_queue);
            }

            ready_queue.push(x);
        }
    }

    void output() {
        double avgWaitingTime = 0;
        // i sort early so to get the right input formula i need to sort again
        sort(processes, processes + numProcesses, [](const Process &p1, const Process &p2) {
            return p1.id < p2.id;
        });

        cout << "\nProcess Completion Time, Turnaround Time, Waiting Time" << endl;
        for (int i = 0; i < numProcesses; i++) {
            cout << "P" << processes[i].id << " "
                 << processes[i].completion_time << " "
                 << processes[i].turnaround_time << " "
                 << processes[i].waiting_time << endl;
            avgWaitingTime += processes[i].waiting_time;
        }
        cout << "Average Waiting Time: " << (double)avgWaitingTime / numProcesses << endl;
    }

    void roundRobin() {
        queue<int> readyQueue;
        int currentTime = 0;
        int programsExecuted = 0;

        checkForArrival(currentTime, readyQueue);

        while (programsExecuted < numProcesses) {
            //if in the input the first process wasn't zero jump to the next smallest one
            if (readyQueue.empty()) {
                int nextArrival = INT_MAX;
                for (int i = 0; i < numProcesses; i++) {
                    if (!processes[i].isComplete && processes[i].arrival_time < nextArrival) {
                        nextArrival = processes[i].arrival_time;
                    }
                }
                currentTime = nextArrival;
                checkForArrival(currentTime, readyQueue);
                continue;
            }

            printQueueState(readyQueue);
            updateQueue(readyQueue, currentTime, programsExecuted);
        }

        cout << "[ Empty ]" << endl;
    }

public:
    RoundRobinScheduler(int n, int quantum) : numProcesses(n), timeQuantum(quantum) {
        processes = new Process[n + 1];
    }

    ~RoundRobinScheduler() {
        delete[] processes;
    }

    void addProcess(int index, int arrival, int burst) {
        processes[index].arrival_time = arrival;
        processes[index].burst_time = burst;
        processes[index].remaining_time = burst;
        processes[index].id = index + 1;
        processes[index].isComplete = false;
        processes[index].inQueue = false;
        processes[index].completion_time = 0;
        processes[index].turnaround_time = 0;
        processes[index].waiting_time = 0;
    }

    void sortByArrivalTime() {
        sort(processes, processes + numProcesses, [](const Process &p1, const Process &p2) {
            return p1.arrival_time < p2.arrival_time;
        });
    }

    void run() {
        roundRobin();
        output();
    }
};

int main() {
    int NumberProcess, timeQuantum;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;
    cout << "the number of processes: ";
    cin >> NumberProcess;

    RoundRobinScheduler scheduler(NumberProcess, timeQuantum);

    for (int i = 0; i < NumberProcess; i++) {
        int arrival, burst;
        cout << "Enter arrival time and burst time of p" << i + 1 << ": ";
        cin >> arrival >> burst;
        scheduler.addProcess(i, arrival, burst);
        cout << endl;
    }

    scheduler.sortByArrivalTime();
    scheduler.run();

    return 0;
}