#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *file_from = fopen(argv[1], "r");
    FILE *file_to = fopen(argv[2], "w");

    if (file_from == NULL || file_to == NULL)
    {
        printf("Something went wrong\n");
        return 1;
    }

    int ch = getc(file_from);

    while (ch != EOF)
    {
        putc(ch, file_to);
        ch = getc(file_from);
    }

    if (!feof(file_from))
    {
        printf("Something went wrong");
        fclose(file_from);
        fclose(file_to);
        return 1;
    }

    fclose(file_from);
    fclose(file_to);

    printf("Process is finished\n");

    return 0;
}