#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;         // Process ID
    int arrivalTime; // Arrival time
    int burstTime;   // Burst time
    int turnaroundTime; // Turnaround time
    int waitingTime;   // Waiting time
};

// Function to calculate the waiting time and turnaround time for each process
void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime > currentTime) {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].turnaroundTime = currentTime + processes[i].burstTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        currentTime += processes[i].burstTime;
    }
}

// Function to print the Gantt chart and burst time numbers
void printGanttChart(struct Process processes[], int n) {
    printf("Gantt Chart:\n");

    // Calculate the total execution time
    int totalTime = 0;
    for (int i = 0; i < n; i++) {
        totalTime += processes[i].burstTime;
    }

    // Print top bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf(" ");
        }
        printf(" ");
    }
    printf("\n|");

    // Print process ID in the middle
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime - 1; j++) {
            printf(" ");
        }
        printf("P%d", processes[i].pid);
        for (int j = 0; j < processes[i].burstTime - 1; j++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n");

    // Print the bottom bar
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf(" ");
        }
        printf(" ");
    }
    printf("\n");

    // Print burst time numbers below the chart
    int currentTime = 0;
    printf("0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf("  ");
        }
        currentTime += processes[i].burstTime;
        if (currentTime > 9) {
            printf("\b"); // Backspace: remove 1 space
        }
        printf("%d", currentTime);
    }
    printf("\n");
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Sort the processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculateTimes(processes, n);

    // Display the process table
    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].arrivalTime + processes[i].turnaroundTime,
               processes[i].turnaroundTime, processes[i].waitingTime);
    }

    printGanttChart(processes, n);

    return 0;
}
/*
AT BT
22
01
23
35
44*/