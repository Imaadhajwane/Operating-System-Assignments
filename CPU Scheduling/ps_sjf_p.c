#include<stdio.h>
#include<stdlib.h>

struct node {
    char pname;
    int btime;
    int atime;
    int restime;
    int ctime;
    int wtime;
};

struct node a[1000], b[1000], c[1000];

void insert(int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        
        // Input Process Name
        printf("Process Name (Single character): ");
        scanf(" %c", &a[i].pname);

        // Input Arrival Time
        do {
            printf("Arrival Time for Process %c: ", a[i].pname);
        } while (scanf("%d", &a[i].atime) != 1 || a[i].atime < 0);

        // Input Burst Time
        do {
            printf("Burst Time for Process %c: ", a[i].pname);
        } while (scanf("%d", &a[i].btime) != 1 || a[i].btime <= 0);

        a[i].wtime = -a[i].atime + 1;
    }
}

void swap(struct node* x, struct node* y) {
    struct node temp = *x;
    *x = *y;
    *y = temp;
}

int btimeSort(const void* a, const void* b) {
    return ((struct node*)a)->btime - ((struct node*)b)->btime;
}

int btimeOppSort(const void* a, const void* b) {
    if (((struct node*)a)->btime != ((struct node*)b)->btime)
        return ((struct node*)a)->btime - ((struct node*)b)->btime;
    return ((struct node*)a)->atime - ((struct node*)b)->atime;
}

int atimeSort(const void* a, const void* b) {
    return ((struct node*)a)->atime - ((struct node*)b)->atime;
}

int k = 0, f = 0, r = 0;

void disp(int nop, int qt) {
    int n = nop, q;
    qsort(a, n, sizeof(struct node), atimeSort);
    int ttime = 0, i;
    int j, tArray[n];
    int alltime = 0;
    int moveLast = 0;
    for (i = 0; i < n; i++) {
        alltime += a[i].btime;
    }
    alltime += a[0].atime;
    for (i = 0; ttime <= alltime;) {
        j = i;
        while (a[j].atime <= ttime && j != n) {
            b[r] = a[j];
            j++;
            r++;
        }
        if (r == f) {
            c[k].pname = 'i';
            c[k].btime = a[j].atime - ttime;
            c[k].atime = ttime;
            ttime += c[k].btime;
            k++;
            continue;
        }
        i = j;
        if (moveLast == 1) {
            qsort(b + f, r - f, sizeof(struct node), btimeSort);
        }

        j = f;
        if (b[j].btime > qt) {
            c[k] = b[j];
            c[k].btime = qt;
            k++;
            b[j].btime -= qt;
            ttime += qt;
            moveLast = 1;
            for (q = 0; q < n; q++) {
                if (b[j].pname != a[q].pname) {
                    a[q].wtime += qt;
                }
            }
        } else {
            c[k] = b[j];
            k++;
            f++;
            ttime += b[j].btime;
            moveLast = 0;
            for (q = 0; q < n; q++) {
                if (b[j].pname != a[q].pname) {
                    a[q].wtime += b[j].btime;
                }
            }
        }
        if (f == r && i >= n)
            break;
    }
    tArray[i] = ttime;
    ttime += a[i].btime;
    for (i = 0; i < k - 1; i++) {
        if (c[i].pname == c[i + 1].pname) {
            c[i].btime += c[i + 1].btime;
            for (j = i + 1; j < k - 1; j++)
                c[j] = c[j + 1];
            k--;
            i--;
        }
    }

    int rtime = 0;
    for (j = 0; j < n; j++) {
        rtime = 0;
        for (i = 0; i < k; i++) {
            if (c[i].pname == a[j].pname) {
                a[j].restime = rtime;
                break;
            }
            rtime += c[i].btime;
        }
    }

    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;

    printf("\nGantt Chart\n");
    rtime = 0;
    for (i = 0; i < k; i++) {
        if (i != k)
            printf("| P%c ", c[i].pname);
        rtime += c[i].btime;
        for (j = 0; j < n; j++) {
            if (a[j].pname == c[i].pname)
                a[j].ctime = rtime;
        }
    }
    printf("\n");
    rtime = 0;
    for (i = 0; i < k + 1; i++) {
        printf("%d\t", rtime);
        tArray[i] = rtime;
        rtime += c[i].btime;
    }

    printf("\n");
    printf("\n");
    printf("P.Name\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < nop && a[i].pname != 'i'; i++) {
        if (a[i].pname == '\0')
            break;
        printf("P%c\t", a[i].pname);
        printf("%d\t", a[i].atime);
        printf("%d\t", a[i].btime);
        printf("%d\t", a[i].ctime);
        printf("%d\t", a[i].wtime + a[i].ctime - rtime + a[i].btime);
        averageTAT += a[i].wtime + a[i].ctime - rtime + a[i].btime;
        printf("%d\t", a[i].wtime + a[i].ctime - rtime);
        averageWaitingTime += a[i].wtime + a[i].ctime - rtime;
        printf("%d\t", a[i].restime - a[i].atime);
        averageResponseTime += a[i].restime - a[i].atime;
        printf("\n");
    }

    printf("Average Response time: %.2f\n", (float)averageResponseTime / (float)nop);
    printf("Average Waiting time: %.2f\n", (float)averageWaitingTime / (float)nop);
    printf("Average TA time: %.2f\n", (float)averageTAT / (float)nop);
}

int main() {
    int nop, choice, i, qt;
    printf("Enter number of processes: ");
    scanf("%d", &nop);
    if (nop <= 0) {
        printf("Invalid input for the number of processes.\n");
        return 1; // Return with an error code
    }
    printf("Enter process details:\n");
    insert(nop);
    disp(nop, 1);
    return 0;
}
