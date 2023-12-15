#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PI acos(-1.0)

long long factorial(const int n)
{
    if (n <= 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

double taylor(const int N, const int x, const int n)
{
    const int parent = getpid();
    int process_counter = 0;
    int pid_t = 1;

    int fd[2];
    pipe(fd);

    while (process_counter < n)
    {
        if (pid_t > 0)
        {
            pid_t = fork();
        }
        process_counter++;
    }

    if (pid_t == 0)
    {
        close(fd[0]);
        const int segment_id = getpid() - parent - x * n - 1;
        double coeff = pow(2 * PI / N, segment_id) * (segment_id % 4 == 3 || segment_id % 4 == 0 ? -1.0 : 1.0);

        if (segment_id % 2 == 0)
        {
            coeff = 0.0;
            printf("child process with pid %d - %f\n", getpid(), coeff);
            write(fd[1], &coeff, sizeof(double));
            close(fd[1]);
            exit(0);
        }

        long long fact = factorial(segment_id);
        long long power = pow(x, segment_id);
        double process_result = coeff * power / fact;
        printf("child process with pid %d - %f\n", getpid(), coeff);
        write(fd[1], &coeff, sizeof(double));
        close(fd[1]);
        exit(0);
    }
    else
    {
        close(fd[1]);
        double result = 0.0;

        for (int i = 0; i < n; i++)
        {
            double temp;
            read(fd[0], &temp, sizeof(double));
            result += temp;
        }

        close(fd[0]);
        while (waitpid(-1, NULL, WNOHANG) > 0) { }
        return result;
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 5)
    {
        printf("wrong number of args, expected 3 but got %d\n", argc);
        return 1;
    }

    FILE *file = fopen(argv[4], "w");

    if (file == NULL)
    {
        printf("Something went wrong\n");
        return 1;
    }

    const int k = atoi(argv[1]);
    const int N = atoi(argv[2]);
    const int n = atoi(argv[3]);

    double results[k];

    for (int i = 0; i < k; i++)
    {
        double taylor_result = taylor(N, i, n);
        printf("sin(2 * PI * %d / %d)=%f\n", i, N, sin(2 * PI * i / N));
        printf("taylor approximation: %f\n", taylor_result);
        results[i] = taylor_result;
        printf("\n");
    }

    for (int i = 0; i < k; i++)
    {
        fprintf(file, "%f\n", results[i]);
    }

    fclose(file);

    return 0;
}
