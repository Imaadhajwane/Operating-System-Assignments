#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 4

int processes, resources;
int max_allocation[MAX_PROCESSES][MAX_RESOURCES];
int current_allocation[MAX_PROCESSES][MAX_RESOURCES];
int available_resources[MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES];

// Function to take user input
void input()
{
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the Max Allocation matrix:\n");
    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            scanf("%d", &max_allocation[i][j]);
        }
    }

    printf("Enter the Current Allocation matrix:\n");
    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            scanf("%d", &current_allocation[i][j]);
            need[i][j] = max_allocation[i][j] - current_allocation[i][j];
        }
        finish[i] = false;
    }

    printf("Enter the Available vector:\n");
    for (int i = 0; i < resources; ++i)
    {
        scanf("%d", &available_resources[i]);
    }
}

// Function to display the current state of the system
void display_frames()
{
    printf("Current Allocation matrix:\n");
    for (int i = 0; i < processes; ++i)
    {
        for (int j = 0; j < resources; ++j)
        {
            printf("%d ", current_allocation[i][j]);
        }
        printf("\n");
    }

    printf("Available vector: ");
    for (int i = 0; i < resources; ++i)
    {
        printf("%d ", available_resources[i]);
    }
    printf("\n");
}

// Function to check if the system is in a safe state
bool is_safe_state(int process)
{
    for (int i = 0; i < resources; ++i)
    {
        if (need[process][i] > available_resources[i])
        {
            return false;
        }
    }
    return true;
}

// Function to execute processes
void execute_processes()
{
    int executed = 0;
    bool deadlock = false;

    while (executed < processes)
    {
        int i;
        bool no_process_executed = true;

        for (i = 0; i < processes; ++i)
        {
            if (!finish[i] && is_safe_state(i))
            {
                printf("Executing process P%d\n", i + 1);

                // Release resources
                for (int j = 0; j < resources; ++j)
                {
                    available_resources[j] += current_allocation[i][j];
                }

                // Mark process as finished
                finish[i] = true;
                executed++;

                // Display the current state
                display_frames();

                no_process_executed = false;
            }
        }

        // If no process can be executed, deadlock detected
        if (no_process_executed)
        {
            deadlock = true;
            break;
        }
    }

    if (deadlock)
    {
        printf("\nSystem is in an unsafe state. Deadlock detected.\n\n");
    }
    else
    {
        printf("\nAll processes executed. System is in a safe state.\n\n");
    }
}

int main()
{
    input();
    display_frames();
    execute_processes();

    return 0;
}

/*
Safe State Example:
Max Allocation Matrix:
7 5 3 4 6
3 2 2 3 3
9 0 2 2 2
2 2 2 0 4
4 3 3 4 4
5 3 3 2 2
Current Allocation Matrix:
3 3 2 2 2
0 1 1 3 3
3 1 2 2 2
2 2 2 0 4
4 3 3 4 4
5 3 3 2 2
Available Vector:
3 1 2 3 2
P1, P3, P4, P6, P2, P5
Unsafe State Example:
Max Allocation Matrix:
7 5 3 4 6
3 2 2 3 3
9 0 2 2 2
2 2 2 0 4
4 3 3 4 4
5 3 3 2 2
Current Allocation Matrix:
3 3 2 2 2
0 1 1 3 3
3 1 2 2 2
2 2 2 0 4
4 3 3 4 4
5 3 3 2 1
Available Vector:
3 1 2 3 2

*/