#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("wrong number of args, expected 2 but got %d\n", argc);
        return 1;
    }
    
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