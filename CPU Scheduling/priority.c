#include <stdio.h>

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int completed;
};

void sortProcesses(struct Process processes[], int n) {
    // Implement a simple bubble sort based on priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                // Swap the processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void priorityScheduling(struct Process processes[], int n) {
    int currentTime = 0;

    while (1) {
        int highestPriority = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].completed == 0) {
                if (highestPriority == -1 || processes[i].priority > processes[highestPriority].priority) {
                    highestPriority = i;
                }
            }
        }

        if (highestPriority == -1) {
            // No process is ready to execute
            currentTime++;
        } else {
            // Execute the highest priority process
            processes[highestPriority].remainingTime--;

            if (processes[highestPriority].remainingTime == 0) {
                // Process has completed execution
                processes[highestPriority].turnaroundTime = currentTime + 1 - processes[highestPriority].arrivalTime;
                processes[highestPriority].completionTime = currentTime + 1;
                processes[highestPriority].waitingTime = processes[highestPriority].turnaroundTime - processes[highestPriority].burstTime;
                processes[highestPriority].completed = 1;
            }

            currentTime++;
        }

        // Check if all processes are completed
        int allCompleted = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].completed == 0) {
                allCompleted = 0;
                break;
            }
        }

        if (allCompleted == 1) {
            break;
        }
    }
}

void displayResults(struct Process processes[], int n) {
    printf("\nPriority\tPID\t\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t%d\t%d\t%d\n",processes[i].priority,processes[i].processId,processes[i].arrivalTime,processes[i].burstTime,processes[i].completionTime,processes[i].turnaroundTime,processes[i].waitingTime);
    }

    float averageWaitingTime = 0, averageTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        averageWaitingTime += processes[i].waitingTime;
        averageTurnaroundTime += processes[i].turnaroundTime;
    }

    averageWaitingTime /= n;
    averageTurnaroundTime /= n;

    printf("\nAverage Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for Process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completed = 0;
    }

    // Sort processes based on priority
    sortProcesses(processes, n);

    // Perform Priority Scheduling
    priorityScheduling(processes, n);

    // Display the results
    displayResults(processes, n);

    return 0;
}
