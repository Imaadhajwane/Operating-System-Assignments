#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;         // Process ID
    int arrivalTime; // Arrival time
    int burstTime;   // Burst time
    int priority;    // Priority
    int finishTime;  // Finish time
    int turnaroundTime; // Turnaround time
    int waitingTime;   // Waiting time
};

// Function to calculate waiting time and turnaround time for each process
void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        int highestPriority = 10000; // A high value as initial highest priority
        int selectedProcess = -1;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= currentTime && processes[j].finishTime == -1) {
                if (processes[j].priority < highestPriority) {
                    highestPriority = processes[j].priority;
                    selectedProcess = j;
                }
            }
        }

        if (selectedProcess == -1) {
            currentTime++;
        } else {
            processes[selectedProcess].finishTime = currentTime + processes[selectedProcess].burstTime;
            processes[selectedProcess].turnaroundTime = processes[selectedProcess].finishTime - processes[selectedProcess].arrivalTime;
            processes[selectedProcess].waitingTime = processes[selectedProcess].turnaroundTime - processes[selectedProcess].burstTime;
            currentTime += processes[selectedProcess].burstTime;
        }
    }
}

// Function to print the Gantt chart
void printGanttChart(struct Process processes[], int n) {
    printf("Gantt Chart:\n");

    int totalTime = 0;
    for (int i = 0; i < n; i++) {
        totalTime += processes[i].burstTime;
    }

    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf(" ");
        }
        printf(" ");
    }
    printf("\n|");

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

    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf(" ");
        }
        printf(" ");
    }
    printf("\n");

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
    printf("| %d", totalTime);

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
        printf("Enter priority for process P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].finishTime = -1;
    }

    // Sort the processes by arrival time and priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime || (processes[j].arrivalTime == processes[j + 1].arrivalTime && processes[j].priority > processes[j + 1].priority)) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    calculateTimes(processes, n);

    // Display the process table
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].pid, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, processes[i].finishTime,
               processes[i].turnaroundTime, processes[i].waitingTime);
    }

    printGanttChart(processes, n);

    return 0;
}
