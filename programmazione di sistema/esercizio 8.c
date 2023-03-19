#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("numero argomenti errati");
        return -1;
    }
    int pid, p1p2[2];
    char stringa[50];

    pipe(p1p2);

    pid = fork();
    if (pid == 0)
    {
        close(p1p2[0]);
        while (1)
        {
            printf("Inserire una stringa: \n");
            scanf("%s", stringa);
            if (strcmp(stringa, "esci") == 0)
            {
                close(p1p2[1]);
                exit(0);
            }
            strcat(stringa, "\n");
            write(p1p2[1], stringa, sizeof(stringa));
        }
    }
    close(p1p2[1]);
    pid = fork();
    if (pid == 0)
    {        
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);
        close(1);
        open(argv[1], O_WRONLY | O_CREAT);
        execl("/usr/bin/sort", "sort", (char *)0);
        return -1;
    }
    close(p1p2[0]);
    wait(&pid);
    return 0;
}
