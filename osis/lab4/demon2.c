#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"

#include "stdlib.h"
#include "stdio.h"


int main() {
    pid_t pid, pidChild, sid;
    int rv;
    FILE *f;
    f = fopen("time.txt", "r");
    int time, generation = 0;
    fscanf(f, "%d", &time);

        pid = fork();
        if (pid == 0){
            while(1){
                generation += 1;
                pidChild = fork();
                usleep(2000000);
                if (pidChild == 0){
                    printf("Child: PID = %d gen - %d\n", getpid(), generation);
                }
                if (pidChild > 0){
                    printf("Parent: my pid - %d gen - %d child pid - %d \n", getpid(), generation, pidChild);
                    exit(1);
                }

            }
            // freopen(NULL, "r", f);
            // fscanf(f, "%d", &time);
            // usleep(time*1000);
            // printf("Child: PID = %d Time = %d\n", getpid(), time);
        }
        if (pid > 0){
            printf("Parent: my pid - %d gen - %d\n", getppid(), generation);
            exit(1);
            // printf("Parent: created child with pid %d\n", pid);
            // printf("Parent: Waiting\n");
            // wait();
            // puts("Parent: stop wait\n");
            // printf("Parent: closed child pid - %d\n", pid);

        }

    // if (pid < 0) {
    //     exit(EXIT_FAILURE);
    // }

    // if (pid == 0){
    //            pid_t pid;
    //     pid = fork();
    //     printf("PID = %d; Time = %d\n", pid, time);     
    // }

    // if (pid > 0) {
    //     printf("PID = %d; Time = %d\n", pid, time);
    //     exit(EXIT_SUCCESS);
    // }

    // umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO); 

    fclose(f);
    exit(0);

    return 0;
}

