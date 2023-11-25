/*Implementation of Longest Job First Scheduling*/

#include<stdio.h>

// Process structure
struct Process {
    int id;          // Process ID
    int burst_time;  // Burst time
};

// Function to perform LJF scheduling
void ljf_scheduling(struct Process processes[], int n) {
    // Sort processes based on burst time in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time < processes[j + 1].burst_time) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Display the order of execution
    printf("Order of Execution: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", processes[i].id);
        if (i != n - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

int main() {
    // Number of processes
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array to store processes
    struct Process processes[n];

    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process P%d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
    }

    // Perform LJF scheduling
    ljf_scheduling(processes, n);

    return 0;
}
