#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "stdio.h"
#include "fcntl.h"
#include "stdlib.h"
#include "time.h"

const int PASS_LENGTH = 8;
const char FIFO_PATH[] = "/tmp/fifo";


char* make_str(int n) {
    return (char*)calloc(1, sizeof(char) * (n + 1));
}

void free_str(char* str) {
    free(str);
}

void init_seed() {
    srand((unsigned int) time(0));
}

void pass_generator(char* str, int n) {
    for (int i = 0; i < n; i++)
        str[i] = rand() % 94 + 33;
}


int main() {
    int fd_fifo;
    char* buffer = make_str(PASS_LENGTH);
    
    int pid = fork();

    if (pid > 0) {
        printf("PID: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    if (access(FIFO_PATH, F_OK) == -1) {
        printf("Server\n");

        unlink(FIFO_PATH);
        if (mkfifo(FIFO_PATH, 0666) == -1) {
            printf("Can't create fifo, Fail\n");
            exit(EXIT_FAILURE);
        }

        init_seed();
        int count = 0;

        while (1) {
            if ((fd_fifo = open(FIFO_PATH, O_RDONLY | O_NONBLOCK)) == -1) {
                printf("Can't open fifo for size check, Fail\n");
                exit(EXIT_FAILURE);
            }
            int c = read(fd_fifo, NULL, PASS_LENGTH);
            close(fd_fifo);

            if (count > 5 || c == 0) {
                if ((fd_fifo = open(FIFO_PATH, O_WRONLY)) == -1) {
                    printf("Can't open fifo for write, Fail\n");
                    exit(EXIT_FAILURE);
                }
                pass_generator(buffer, PASS_LENGTH);
                write(fd_fifo, buffer, PASS_LENGTH);
                close(fd_fifo);

                if (count > 5)
                    count = 0;
            } 
            
            count++;
            // sleep(1);
        }

        unlink(FIFO_PATH);
    }
    else {
        printf("Client\n");
        
        while (1) {
            if ((fd_fifo = open(FIFO_PATH, O_RDONLY)) == -1) {
                printf("Can't open fifo for read, Fail\n");
                exit(EXIT_FAILURE);
            }
            read(fd_fifo, buffer, PASS_LENGTH);
            close(fd_fifo);
            
            if ((fd_fifo = open(FIFO_PATH, O_WRONLY)) == -1) {
                printf("Can't open fifo for truncate, Fail\n");
                exit(EXIT_FAILURE);
            }
            close(fd_fifo);

            printf("Pass: %s\n", buffer);
            }
            sleep(1);
    }


    free_str(buffer);
    return 0;
}
