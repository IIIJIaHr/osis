#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"

#include "stdlib.h"
#include "stdio.h"


int main() {
    pid_t pid, sid;
    int rv;
    FILE *f;
    f = fopen("time.txt", "r");
    int time, greed;
    fscanf(f, "%d", &time);

    for(greed = 0; greed < 50; greed++){
        pid = fork();
        if (pid < 0){
            exit(0);
        }
        if (pid == 0){
            freopen(NULL, "r", f);
            fscanf(f, "%d", &time);
            usleep(time);
            printf("Child: PID = %d Parent PID = %d Time = %d\n", getpid(), getppid(), time);
        }
        if (pid > 0){
            printf("Parent: PID = %d Child PID = %d Greed = %d\n", getpid(), pid, greed);
            exit(1);
        }

    }

    fclose(f);
    return 0;
}

