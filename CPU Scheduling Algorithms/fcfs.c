/*Implement a First-Come-First-Serve (FCFS) scheduling algorithm for a
set of processes in an operating system and calculate the average waiting
time, turnaround time, and response time.
*/

#include <stdio.h>
struct Process {
int id;
int arrivalTime;
int burstTime;
int waitingTime;
int turnaroundTime;
int responseTime;
};
void calculateAverageTimes(struct Process processes[], int n) {
int totalWaitingTime = 0;
int totalTurnaroundTime = 0;
int totalResponseTime = 0;
for (int i = 0; i < n; i++) {
if (i == 0) {
processes[i].waitingTime = 0;
} else {
processes[i].waitingTime = processes[i - 1].turnaroundTime - processes[i].arrivalTime;
if (processes[i].waitingTime < 0) {
processes[i].waitingTime = 0;
}
}
processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
processes[i].responseTime = processes[i].waitingTime;
totalWaitingTime += processes[i].waitingTime;
totalTurnaroundTime += processes[i].turnaroundTime;
totalResponseTime += processes[i].responseTime;
}
double averageWaitingTime = (double)totalWaitingTime / n;
double averageTurnaroundTime = (double)totalTurnaroundTime / n;
double averageResponseTime = (double)totalResponseTime / n;
printf("Average Waiting Time: %.2lf\n", averageWaitingTime);
printf("Average Turnaround Time: %.2lf\n", averageTurnaroundTime);
printf("Average Response Time: %.2lf\n", averageResponseTime);
}
int main() {
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
struct Process processes[n];
for (int i = 0; i < n; i++) {
processes[i].id = i + 1;
printf("Enter arrival time for process %d: ", i + 1);
scanf("%d", &processes[i].arrivalTime);
printf("Enter burst time for process %d: ", i + 1);
scanf("%d", &processes[i].burstTime);
}
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
struct Process temp = processes[j];
processes[j] = processes[j + 1];
processes[j + 1] = temp;
}
}
}
calculateAverageTimes(processes, n);
return 0;
}
