#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 4

int max[NUM_PROCESSES][NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
int available[NUM_RESOURCES];

bool isSafe(int work[], int finish[], int safeSeq[])
{
    int count = 0;
    while (count < NUM_PROCESSES)
    {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < NUM_RESOURCES; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSeq[count] = i;
                    count++;
                    found = true;

                    // Display step-by-step process
                    printf("Step %d:\n", count);
                    printf("Allocated resources for P%d\n", i);
                    printf("Updated Available Matrix: ");
                    for (int k = 0; k < NUM_RESOURCES; k++)
                    {
                        printf("%d ", work[k]);
                    }
                    printf("\n");
                    printf("Need Matrix:\n");
                    for (int k = 0; k < NUM_PROCESSES; k++)
                    {
                        for (int l = 0; l < NUM_RESOURCES; l++)
                        {
                            printf("%d ", need[k][l]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            }
        }
        if (!found)
        {
            return false; // No process can be allocated; system is in an unsafe state
        }
    }
    return true; // System is in a safe state
}

int main()
{
    int work[NUM_RESOURCES];
    int finish[NUM_PROCESSES] = {0};
    int safeSeq[NUM_PROCESSES];

    printf("Enter the Maximum Allocation Matrix:\n");
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        for (int j = 0; j < NUM_RESOURCES; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        for (int j = 0; j < NUM_RESOURCES; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter the Total Resources Available:\n");
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        work[i] = available[i];
    }

    if (isSafe(work, finish, safeSeq))
    {
        printf("System is in a safe state; no deadlock.\nSafe Sequence:");
        for (int i = 0; i < NUM_PROCESSES; i++)
        {
            printf("P%d", safeSeq[i]);
            if (i < NUM_PROCESSES - 1)
            {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    else
    {
        printf("System is in an unsafe state; deadlock detected.\n");
    }

    return 0;
}
/*
pseudo 
// Define constants for the number of processes and resources
#define NUM_PROCESSES 5
#define NUM_RESOURCES 4

// Declare global arrays for maximum, allocation, need, and available matrices
int max[NUM_PROCESSES][NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
int available[NUM_RESOURCES];

// Function to check if the system is in a safe state and determine the safe sequence
bool isSafe(int work[], int finish[], int safeSeq[]) {
    int count = 0;

    // Continue until all processes are finished
    while (count < NUM_PROCESSES) {
        bool found = false;

        // Iterate through each process
        for (int i = 0; i < NUM_PROCESSES; i++) {
            // Check if the process is not finished
            if (!finish[i]) {
                bool canAllocate = true;

                // Check if the process can be allocated resources
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                // If the process can be allocated, update the work matrix and finish the process
                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSeq[count] = i;
                    count++;
                    found = true;

                    // Display step-by-step process
                    printf("Step %d:\n", count);
                    printf("Allocated resources for P%d\n", i);
                    printf("Updated Available Matrix: ");
                    for (int k = 0; k < NUM_RESOURCES; k++) {
                        printf("%d ", work[k]);
                    }
                    printf("\n");
                    printf("Need Matrix:\n");
                    for (int k = 0; k < NUM_PROCESSES; k++) {
                        for (int l = 0; l < NUM_RESOURCES; l++) {
                            printf("%d ", need[k][l]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                }
            }
        }

        // If no process can be allocated, the system is in an unsafe state
        if (!found) {
            return false;
        }
    }

    // If all processes are finished, the system is in a safe state
    return true;
}

// Main function
int main() {
    int work[NUM_RESOURCES];
    int finish[NUM_PROCESSES] = {0};
    int safeSeq[NUM_PROCESSES];

    // Input the Maximum Allocation Matrix
    printf("Enter the Maximum Allocation Matrix:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input the Allocation Matrix and calculate the Need Matrix
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Input the Total Resources Available
    printf("Enter the Total Resources Available:\n");
    for (int i = 0; i < NUM_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize the work matrix with available resources
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    // Check if the system is in a safe state and determine the safe sequence
    if (isSafe(work, finish, safeSeq)) {
        printf("System is in a safe state; no deadlock.\nSafe Sequence:");
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("P%d", safeSeq[i]);
            if (i < NUM_PROCESSES - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("System is in an unsafe state; deadlock detected.\n");
    }

    return 0;
}
*/
/*
input
max
0 0 1 2 
1 7 5 0 
2 3 5 6 
0 6 5 2 
0 6 5 6 

allocation
0 0 1 2 
1 0 0 0 
1 3 5 4
0 6 3 2 
0 0 1 4 

available 
1 5 2 0 

total=available+allocation
available=sum of allocation - total
3 14 12 12*/