#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
    int pid;
    int p1p2[2];
    int p2p3[2];
    int p3p0[2];

    pipe(p1p2);
    pid = fork();
    if (pid == 0)
    {
        close(p1p2[READ]);
        close(WRITE);
        dup(p1p2[WRITE]);
        close(p1p2[WRITE]);
        execl("/bin/cat", "cat", argv[1], (char *)0);
        return -1;
    }

    pipe(p2p3);
    pid = fork();
    if (pid == 0)
    {
        close(p1p2[WRITE]);
        close(READ);
        dup(p1p2[READ]);
        close(p1p2[READ]);

        close(p2p3[READ]);
        close(WRITE);
        dup(p1p2[WRITE]);
        close(p1p2[WRITE]);
        execl("/usr/bin/awk", "awk", "{print $4}", (char *)0);
        return -1;
    }

    pipe(p3p0);
    pid = fork();
    if (pid == 0)
    {
        close(p1p2[WRITE]);
        close(p1p2[READ]);
        close(p2p3[WRITE]);
        close(READ);
        dup(p1p2[READ]);
        close(p1p2[READ]);

        close(p3p0[READ]);
        close(WRITE);
        dup(p1p2[WRITE]);
        close(p1p2[WRITE]);
        execl("/usr/bin/tail", "tail", "-n", "+2", (char *)0);
        return -1;
    }
    close(p1p2[WRITE]);
    close(p1p2[READ]);
    close(p2p3[WRITE]);
    close(p2p3[READ]);
    close(p3p0[WRITE]);

    double totale;
    char buff;
    char importo[1000];

    while (read(p3p0[READ], buff, strlen(buff))>0)
    {
        
        totale = 
    }
}