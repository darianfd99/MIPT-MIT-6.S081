//
// Created by darianfd99 on 12/1/23.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);

    if(fork() == 0){
        close(p1[1]);
        close(p2[0]);
        char buff[1];
        int n = read(p1[0], buff, 1);
        if (n != 1){
            fprintf(2, "error reading from pipe\n");
            exit(1);
        }
        close(p1[0]);

        fprintf(0, "%d: received ping\n", getpid());

        int wroteN = write(p2[1], buff, 1);
        if (wroteN != 1){
            fprintf(2, "error writing to the pipe\n");
            exit(1);
        }
        close(p2[1]);
        exit(0);
    }
    close(p1[0]);
    close(p2[1]);
    int n = write(p1[1], "a", 1);
    if (n != 1){
        fprintf(2, "error writing to the pipe\n");
        exit(1);
    }
    close(p1[1]);

    int buff[1];
    int readN = read(p2[0], buff, 1);
    if (readN != 1){
        fprintf(2, "error reading from pipe\n");
        exit(1);
    }
    close(p2[0]);

    fprintf(0, "%d: received pong\n", getpid());
    exit(0);
}