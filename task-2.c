#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE *file = fopen(argv[1], "w");

    if (file == NULL)
    {
        printf("Something went wrong\n");
        return 1;
    }

    char ch = getchar();

    while (ch != 6)
    {
        fputc(ch, file);
        ch = getchar();
    }

    fclose(file);
    printf("Process is finished\n");

    return 0;
}