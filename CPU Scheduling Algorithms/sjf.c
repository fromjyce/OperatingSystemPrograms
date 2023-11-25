/*Implement the Shortest Job First (SJF) scheduling algorithm on a UNIXbased operating system, and calculate the average response time for a set of
processes.*/

#include <stdio.h>
#include <stdlib.h>
struct Process {
int id;
int burst_time;
int waiting_time;
int turnaround_time;
int response_time;
};
void calculateTimes(struct Process processes[], int n) {
processes[0].waiting_time = 0;
processes[0].response_time = 0;
processes[0].turnaround_time = processes[0].burst_time;
for (int i = 1; i < n; i++) {
processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
processes[i].response_time = processes[i].waiting_time;
processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
}
}
void calculateAverageTimes(struct Process processes[], int n, float *avg_waiting_time,
float *avg_turnaround_time, float *avg_response_time) {
int total_waiting_time = 0;
int total_turnaround_time = 0;
int total_response_time = 0;
for (int i = 0; i < n; i++) {
total_waiting_time += processes[i].waiting_time;
total_turnaround_time += processes[i].turnaround_time;
total_response_time += processes[i].response_time;
}
*avg_waiting_time = (float)total_waiting_time / n;
*avg_turnaround_time = (float)total_turnaround_time / n;
*avg_response_time = (float)total_response_time / n;
}
void sjfScheduling(struct Process processes[], int n) {
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (processes[j].burst_time > processes[j + 1].burst_time) {
struct Process temp = processes[j];
processes[j] = processes[j + 1];
processes[j + 1] = temp;
}
}
}
calculateTimes(processes, n);
}
int main() {
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
struct Process processes[n];
for (int i = 0; i < n; i++) {
processes[i].id = i + 1;
printf("Enter burst time for process P%d: ", i + 1);
scanf("%d", &processes[i].burst_time);
}
sjfScheduling(processes, n);
float avg_waiting_time, avg_turnaround_time, avg_response_time;
calculateAverageTimes(processes, n, &avg_waiting_time, &avg_turnaround_time, &avg_response_time);
printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
printf("Average Response Time: %.2f\n", avg_response_time);
return 0;
}