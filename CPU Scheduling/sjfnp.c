#include <stdio.h>
#include <stdlib.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burstTime > processes[j + 1].burstTime) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        currentTime = processes[i].completionTime;
    }
}

void displaySchedule(struct Process processes[], int n) {
    printf("\nProcess Schedule:\n");
    printf("----------------------------------------------------------------\n");
    printf("| ProcessID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %-10d | %-13d | %-10d | %-15d | %-15d | %-12d |\n", processes[i].processID,
               processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime,
               processes[i].turnaroundTime, processes[i].waitingTime);
    }
    printf("----------------------------------------------------------------\n");
}

void generateGanttChart(struct Process processes[], int n) {
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n|");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime - 1; j++) {
            printf(" ");
        }
        printf("P%d|", processes[i].processID);
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burstTime; j++) {
            printf("--");
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    int n;

    // Get the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Get process details from the user
    for (int i = 0; i < n; i++) {
        processes[i].processID = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Sort processes based on burst time using Bubble Sort
    bubbleSort(processes, n);

    // Calculate turnaround time and waiting time for processes
    calculateTimes(processes, n);

    // Display the schedule
    displaySchedule(processes, n);

    // Generate Gantt chart
    generateGanttChart(processes, n);

    return 0;
}
