/*Implementation of Highest Response Ratio Next Scheduling*/

#include <stdio.h>

// Defining process

struct process {

char name;

int at, bt, ct, wt, tt;

int completed;

} p[5];

int n;

// Sorting of processes by their Arrival Time

void sortByArrivalTime()

{

struct process temp;

int i, j;

// Selection Sort
for (i = 0; i < n - 1; i++) {

for (j = i + 1; j < n; j++) {

if (p[i].at > p[j].at) {

temp = p[i];

p[i] = p[j];

p[j] = temp;

}

}

}

}

void main()

{

int i, j, t, sumbt = 0;

//for process names P1,P2 etc.

char c[6] = {'1','2','3','4','5','\0'};

     float avgWt = 0.0;

     float avgTt = 0.0; 

n = 5;
//input arrival times

int arrTime[] = { 0, 2, 4, 5, 7 };

//input burst times

int brstTime[] = { 2, 6, 7, 3, 5 };

// Initializing

for (i = 0; i < n; i++) {

p[i].name =c[i];

p[i].at = arrTime[i];

p[i].bt = brstTime[i];

//Completion status (Pending - 0, Completed - 1)

p[i].completed = 0;

//sum of all Burst Times

sumbt += p[i].bt;
}
// Sorting the structure by arrival time of processes from the ready queue

sortByArrivalTime();

printf("\nProcess\tArrival Time\tBurst Time\tTurn Around Time\tWaiting Time");

for (t = p[0].at; t < sumbt;) {

// Lower limit to HRR

float hrr = -9999;

// Response Ratio

float temp;

// Variable for storing next selected process

int loc;

for (i = 0; i < n; i++) {
// This is to check if the process has arrived from the ready queue and is incomplete or complete

if (p[i].at <= t && p[i].completed != 1) {

// Calculating Response Ratio

temp = (p[i].bt + (t - p[i].at)) / p[i].bt;

// Checking for Highest Response Ratio

if (hrr < temp) {

// Storing Response Ratio

hrr = temp;

// Storing Location
loc = i;

}

}

}

// Updating time

t += p[loc].bt;

// Calculating Waiting Time

p[loc].wt = t - p[loc].at - p[loc].bt;

// Calculating Turn Around Time

p[loc].tt = t - p[loc].at;

// Sum of TAT

avgTt += p[loc].tt;

// Updating Completion Status

p[loc].completed = 1;

/ Sum of Waiting Time

avgWt += p[loc].wt;

printf("\nP%c\t\t%d\t\t", p[loc].name, p[loc].at);

printf("%d\t\t%d\t\t%d", p[loc].bt, p[loc].tt, p[loc].wt);

}

printf("\nAverage Waiting Time:%f\n", avgWt / n);

printf("Average Turn Around Time:%f\n", avgTt / n);

}
