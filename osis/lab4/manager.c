#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "signal.h"

#include "stdlib.h"
#include "stdio.h"


void handle_signal(int signal);
void change_speed();

int speed = 0;
int step = 0;
FILE *f = NULL;
pid_t sid;

const char* filename = "time.txt";

int main() {

    printf("%d\n", getpid());

    f = fopen(filename, "r");
    fscanf(f, "%d", &speed);
    step = 1000000;

    signal(SIGUSR1, handle_signal);
    signal(SIGINT, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (1) { 
        usleep(100);
    }
}


void handle_signal(int signal) {
    switch (signal) {
    
        case SIGUSR1:
            speed += step; 
            change_speed();
            break;
        
        case SIGUSR2: 
            if (speed > 0) {
                speed -= step;
            }
            change_speed();
            break;

        case SIGINT:
            fclose(f);
            exit(0);
            break;
    }
}

void change_speed() {
    freopen(NULL, "w", f);
    fprintf(f, "%d", speed);
    fflush(f);
}
