

#include <stdio.h>

struct Process {
    int pid, at, bt, rt, ct, wt, tat;
};

int main() {
    struct Process p[20], temp;
    int n, tq, time = 0, done = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    // Sort processes by arrival time
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++)
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    printf("\nExecution Sequence: ");

    while(done < n) {
        int executed = 0;

        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0 && p[i].at <= time) {
                executed = 1;

                printf("P%d ", p[i].pid);

                if(p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    done++;
                }
            }
        }

        if(!executed) {
            time++;
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid, p[i].at, p[i].bt,
        p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
}