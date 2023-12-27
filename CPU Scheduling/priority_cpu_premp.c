#include <stdio.h>
#include <stdbool.h>

struct Process {
    int process_id;
    int priority;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int response_time;
    int turnaround_time;
    int waiting_time;
    bool completed;
};

// Function to find the process with the highest priority
int findHighestPriority(struct Process processes[], int n, int current_time) {
    int highest_priority = -1;
    int highest_priority_value = 99999; // A large initial value

    for (int i = 0; i < n; i++) {
        if (!processes[i].completed && processes[i].arrival_time <= current_time) {
            if (processes[i].priority < highest_priority_value) {
                highest_priority_value = processes[i].priority;
                highest_priority = i;
            }
        }
    }

    return highest_priority;
}

// Function to calculate response time, turnaround time, waiting time, and average waiting time for Priority scheduling
void calculatePriorityPreemptive(struct Process processes[], int n) {
    int total_waiting_time = 0;
    float average_waiting_time = 0;
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int highest_priority = findHighestPriority(processes, n, current_time);

        if (highest_priority == -1) {
            current_time++;
        } else {
            struct Process *current_process = &processes[highest_priority];

            if (current_process->response_time == -1) {
                current_process->response_time = current_time - current_process->arrival_time;
            }

            current_process->remaining_time--;

            if (current_process->remaining_time == 0) {
                current_process->turnaround_time = current_time + 1 - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
                total_waiting_time += current_process->waiting_time;
                current_process->completed = true;
                completed_processes++;
            }

            current_time++;
        }
    }

    // Calculate average waiting time
    average_waiting_time = (float)total_waiting_time / n;

    // Print process details
    printf("\nProcess\tPriority\tBurst Time\tResponse Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].priority,
               processes[i].burst_time, processes[i].response_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Print average waiting time
    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Declare an array of processes
    struct Process processes[n];

    // Input details for each process
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);

        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = false;
        processes[i].response_time = -1;
    }

    // Perform Priority preemptive scheduling
    calculatePriorityPreemptive(processes, n);

    return 0;
}
