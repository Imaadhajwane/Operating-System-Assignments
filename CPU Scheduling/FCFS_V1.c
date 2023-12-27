#include <stdio.h>

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int startTime;
    int finishTime;
    int turnaroundTime;
    int waitingTime;
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void displayGanttChart(struct Process processes[], int n) {
    int currentTime = 0;
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        processes[i].startTime = currentTime;
        processes[i].finishTime = currentTime + processes[i].burstTime;

        // Print process
        printf(" P%d ", processes[i].processId);

        // Print Idle time or completion
        if (i < n - 1) {
            int idleTime = processes[i + 1].arrivalTime - processes[i].finishTime;
            if (idleTime > 0) {
                printf("| Idle |");
                currentTime += idleTime;
            }
        }

        // Update currentTime
        currentTime = processes[i].finishTime;

        // Print process completion time
        printf("| %d ", processes[i].finishTime);
    }
    printf("|\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of processes. Exiting.\n");
        return 1;
    }

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);

        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);

        if (processes[i].arrivalTime < 0 || processes[i].burstTime < 0) {
            printf("Invalid input. Please enter non-negative values. Exiting.\n");
            return 1;
        }
    }

    sortProcesses(processes, n);

    displayGanttChart(processes, n);


    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    int totalIdleTime = 0;
    int completionTime = processes[n - 1].finishTime;

    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
        if (processes[i].turnaroundTime < 0) {
            processes[i].turnaroundTime = 0;  // Correct negative turnaround time
        }
        totalTurnaroundTime += processes[i].turnaroundTime;

        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        if (processes[i].waitingTime < 0) {
            processes[i].waitingTime = 0;  // Correct negative waiting time
        }
        totalWaitingTime += processes[i].waitingTime;

        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].processId, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].finishTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    totalIdleTime = completionTime - processes[n - 1].finishTime;

    float cpuUtilization = (float)(completionTime - totalIdleTime) / completionTime;

    printf("\nCompletion Time: %d\n", completionTime);
    printf("Total Turnaround Time: %d\n", totalTurnaroundTime);
    printf("Total Waiting Time: %d\n", totalWaitingTime);
    printf("Idle Time: %d\n", totalIdleTime);
    printf("CPU Utilization: %.2f%%\n", cpuUtilization * 100);

    return 0;
}

