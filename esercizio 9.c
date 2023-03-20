#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("numero argomenti errato");
        return -1;
    }

    int pid, p1p2[2], nread, fd;
    char buffer;

    pipe(p1p2);
    pid = fork();
    if (pid == 0)
    {
        close(p1p2[0]);
        fd=open(argv[1], O_RDONLY);
        while ((nread = read(fd, &buffer, sizeof(buffer))>0))
        {
            write(p1p2[1], &buffer, nread);
        }
        close(p1p2[1]);
        exit(0);
    }

    pid = fork();
    if (pid == 0)
    {
        close(p1p2[1]);        
        fd=open(argv[2], O_WRONLY  | O_CREAT, 0777);
        while ((nread=read(p1p2[0], &buffer, sizeof(buffer)))>0)
        {
            write(fd, &buffer, nread);
        }
        close(p1p2[0]);
        exit(0);
    }
    close(p1p2[0]);
    close(p1p2[1]);
    return 0;
}