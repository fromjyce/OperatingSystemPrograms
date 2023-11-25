/*Implementation of Longest Remaining Time First Scheduling*/

#include<stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortProcessesByArrivalTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void sortProcessesByRemainingTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].remaining_time < processes[j + 1].remaining_time) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void findWaitingTime(struct Process processes[], int n, int waitingTime[]) {
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++) {
        waitingTime[i] = processes[i - 1].burst_time + waitingTime[i - 1];
    }
}

void findTurnaroundTime(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = processes[i].burst_time + waitingTime[i];
    }
}

void findAverageTime(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n];

    findWaitingTime(processes, n, waitingTime);
    findTurnaroundTime(processes, n, waitingTime, turnaroundTime);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nProcess\t  Arrival Time\t  Burst Time\t  Waiting"
           " Time\t  Turn-Around Time\n");

    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id,
               processes[i].arrival_time, processes[i].burst_time, waitingTime[i], turnaroundTime[i]);
    }

    printf("\nAverage waiting time: %.2f", totalWaitingTime / n);
    printf("\nAverage turnaround time: %.2f\n", totalTurnaroundTime / n);
}

void LRTFScheduling(struct Process processes[], int n) {
    int currentTime = 0;

    // Sort processes by arrival time
    sortProcessesByArrivalTime(processes, n);

    // Set remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (1) {
        int isAllProcessesExecuted = 1;

        // Sort processes by remaining time
        sortProcessesByRemainingTime(processes, n);

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0) {
                isAllProcessesExecuted = 0;

                // Execute the process with the longest remaining time
                printf("Executing process %d at time %d\n", processes[i].process_id, currentTime);
                currentTime += processes[i].remaining_time;
                processes[i].remaining_time = 0;
            }
        }

        if (isAllProcessesExecuted) {
            break;
        }
    }

    // Calculate and display turnaround time and waiting time
    findAverageTime(processes, n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    LRTFScheduling(processes, n);

    return 0;
}
