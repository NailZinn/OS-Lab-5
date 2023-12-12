#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("wrong number of args, expected 2 but got %d\n", argc);
        return 1;
    }
    printf("%s\n", argv[1]);
    return 0;
}