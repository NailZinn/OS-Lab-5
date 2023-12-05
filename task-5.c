#include <stdio.h>
#include <dirent.h>

void print_directory(DIR* directory)
{
    struct dirent *directory_entry = readdir(directory);

    while (directory_entry != NULL)
    {
        printf("%s\n", directory_entry->d_name);
        directory_entry = readdir(directory);
    }
}

int main(int argc, char const *argv[])
{
    DIR *current_directory = opendir(".");
    DIR *user_directory = opendir(argv[1]);

    if (current_directory == NULL || user_directory == NULL)
    {
        printf("Something went wrong\n");
        return 1;
    }

    printf("Current directory\n");
    print_directory(current_directory);
    printf("\nUser directory\n");
    print_directory(user_directory);

    closedir(user_directory);
    closedir(current_directory);

    return 0;
}
