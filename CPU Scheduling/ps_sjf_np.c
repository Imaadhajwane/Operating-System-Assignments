#include<stdio.h>
#include<stdlib.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sortat(int p[], int at[], int bt[], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(at[i] > at[j]) {
                swap(&p[i], &p[j]);
                swap(&at[i], &at[j]);
                swap(&bt[i], &bt[j]);
            } else if(at[i] == at[j]) {
                if(bt[i] > bt[j]) {
                    swap(&p[i], &p[j]);
                    swap(&at[i], &at[j]);
                    swap(&bt[i], &bt[j]);
                }
            }
        }
    }
}

void tatwt(int ct[], int at[], int bt[], int tat[], int wt[], int n) {
    int i;
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
}

void generateGanttChart(int p[], int n) {
    printf("\n\nGantt Chart:\n");

    for (int i = 0; i < n; i++) {
        printf("| P%d ", p[i]);
    }
    printf("|\n");
}

int main() {
    int *p, *at, *bt, *tat, *wt, *ct, pos, i, j, min = 1000, n;
    float awt = 0, atat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    p = (int*)malloc(n * sizeof(int));
    at = (int*)malloc(n * sizeof(int));
    bt = (int*)malloc(n * sizeof(int));
    ct = (int*)malloc(n * sizeof(int));
    wt = (int*)malloc(n * sizeof(int));
    tat = (int*)malloc(n * sizeof(int));

    printf("Enter the process IDs:\n");
    for(i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &p[i]);
    }

    printf("Enter the arrival times:\n");
    for(i = 0; i < n; i++) {
        printf("Arrival time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
    }

    printf("Enter the burst times:\n");
    for(i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    sortat(p, at, bt, n);

    ct[0] = at[0] + bt[0];
    for(i = 1; i < n; i++) {
        for(j = i; j < n; j++) {
            if(at[j] <= ct[i-1]) {
                if(bt[j] < min) {
                    min = bt[j];
                    pos = j;
                }
            }
        }

        swap(&p[i], &p[pos]);
        swap(&at[i], &at[pos]);
        swap(&bt[i], &bt[pos]);
        min = 1000;
        ct[i] = ct[i-1] + bt[i];
    }

    tatwt(ct, at, bt, tat, wt, n);

    printf("\nPID\t Arrival Time\t Burst Time\t Completion Time\t Turnaround Time\t Waiting Time");
    for(i = 0; i < n; i++) {
        printf("\n%d\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t %d", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    generateGanttChart(p, n);

    for(i = 0; i < n; i++) {
        atat += tat[i];
        awt += wt[i];
    }

    atat = atat / n;
    awt = awt / n;
    printf("\nAverage Turnaround Time: %.2f\n", atat);
    printf("Average Waiting Time: %.2f\n", awt);

    // Free allocated memory
    free(p);
    free(at);
    free(bt);
    free(ct);
    free(wt);
    free(tat);

    return 0;
}
