#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int pid = fork();

    if (pid > 0)
    {
        pid = fork();
    }

    struct timeb ttimeb;
    ftime(&ttimeb);
    struct tm *timeinfo = localtime(&ttimeb.time);

    printf("Current process %d\n", getpid());
    printf("Parent process %d\n", getpid());
    printf("%d:%d:%d:%d\n", timeinfo->tm_hour, timeinfo-> tm_min, timeinfo->tm_sec, ttimeb.millitm);

    if (pid > 0)
    {
        system("ps -x");
    }

    return 0;
}
