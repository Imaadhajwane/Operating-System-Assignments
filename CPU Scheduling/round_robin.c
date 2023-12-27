 #include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int finish_time;
    int response_time;
    int turnaround_time;
    int waiting_time;
};

// Function to calculate Round Robin scheduling
void calculateRoundRobin(struct Process processes[], int n, int time_quantum) {
    int current_time = 0;
    int total_waiting_time = 0;
    float average_waiting_time = 0;
    int remaining_processes = n;

    // Use an array to keep track of whether a process is completed
    int completed[n];
    for (int i = 0; i < n; i++) {
        completed[i] = 0;
    }

    printf("Gantt Chart:\n");
    while (remaining_processes > 0) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) {
                printf("| P%d ", processes[i].process_id);

                if (processes[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].finish_time = current_time;
                    processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    total_waiting_time += processes[i].waiting_time;
                    completed[i] = 1;
                    remaining_processes--;
                }

                executed = 1;
            }
        }

        if (executed == 0) {
            printf("| Idle ");
            current_time++;
        }
    }
    printf("|\n");

    // Calculate response time for each process
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (completed[j] == 1 && processes[i].process_id == j + 1) {
                processes[i].response_time = processes[j].finish_time - processes[j].burst_time - processes[j].arrival_time;
                break;
            }
        }
    }

    // Calculate average waiting time
    average_waiting_time = (float)total_waiting_time / n;

    // Print process details
    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tResponse Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].finish_time, processes[i].response_time,
               processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
}

int main() {
    int n, time_quantum;

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
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Perform Round Robin scheduling
    calculateRoundRobin(processes, n, time_quantum);

    return 0;
}
