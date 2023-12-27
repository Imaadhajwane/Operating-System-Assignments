#include <stdio.h>

#define MAX_PROCESSES 6
#define MAX_RESOURCES 5

int available[MAX_RESOURCES];
int max_allocation[MAX_PROCESSES][MAX_RESOURCES];
int current_allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];
int safe_sequence[MAX_PROCESSES];

void input_matrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], int rows, int cols, const char *name) {
    printf("Enter the %s matrix:\n", name);
    for (int i = 0; i < rows; ++i) {
        printf("Process %d: ", i);
        for (int j = 0; j < cols; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void calculate_need() {
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            need[i][j] = max_allocation[i][j] - current_allocation[i][j];
        }
    }
}

int is_safe() {
    int work[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        work[i] = available[i];
    }

    int count = 0;

    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finish[i]) {
                int can_allocate = 1;
                for (int j = 0; j < MAX_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < MAX_RESOURCES; ++j) {
                        work[j] += current_allocation[i][j];
                    }
                    finish[i] = 1;
                    safe_sequence[count++] = i;
                    found = 1;
                }
            }
        }

        if (!found) {
            break;  // If no process can be allocated, exit the loop
        }
    }

    return count == MAX_PROCESSES;
}

int main() {
    // Input total available resources
    printf("Enter total available resources: ");
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        printf("Enter resource %d: ", i + 1);
        scanf("%d", &available[i]);
    }

    // Input maximum allocation matrix
    input_matrix(max_allocation, MAX_PROCESSES, MAX_RESOURCES, "maximum allocation");

    // Input current allocation matrix
    input_matrix(current_allocation, MAX_PROCESSES, MAX_RESOURCES, "current allocation");

    // Calculate the need matrix
    calculate_need();

    // Check if the system is in a safe state
    if (is_safe()) {
        printf("System is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < MAX_PROCESSES; ++i) {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        printf("Deadlock detected.\n");
    }

    return 0;
}
