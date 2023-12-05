#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Something went wrong\n");
        return 1;
    }

    const int N = atoi(argv[2]);
    int ch = getc(file);
    int number_of_new_lines = 0;

    while (ch != EOF)
    {
        printf("%c", ch);

        if (ch == '\n')
        {
            number_of_new_lines++;
        }
        if (N != 0 && number_of_new_lines == N)
        {
            number_of_new_lines = 0;
            printf("Press any key: ");
            while (getchar() != '\n') { }
        }

        ch = getc(file);
    }

    if (!feof(file))
    {
        printf("Something went wrong\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("\nProcess is finished\n");

    return 0;
}