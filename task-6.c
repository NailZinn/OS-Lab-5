#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int traverse_directory(const char* path, int min_size, int max_size, FILE *output_file)
{
    DIR *directory = opendir(path);
    int files_seen = 0;

    if (directory == NULL)
    {
        printf("directory is null\n");
        return 0;
    }

    struct dirent *directory_entry = readdir(directory);
    struct stat entry_stat;

#ifdef _WIN32
    char directory_name[266];
#endif
    char directory_entry_name[266];
    char file_entry[266];

    while (directory_entry != NULL)
    {
        snprintf(directory_entry_name, sizeof(directory_entry_name), "%s/%s", path, directory_entry->d_name);
        stat(directory_entry_name, &entry_stat);

        if (S_ISDIR(entry_stat.st_mode))
        {
            if (strcmp(directory_entry->d_name, ".") != 0 && strcmp(directory_entry->d_name, "..") != 0)
            {
                files_seen += traverse_directory(directory_entry_name, min_size, max_size, output_file);
            }
            directory_entry = readdir(directory);
            continue;
        }

        files_seen++;

        if (entry_stat.st_size >= min_size && entry_stat.st_size <= max_size)
        {
#ifdef _WIN32
            strncpy(directory_name, directory->dd_name, strlen(directory->dd_name) - 1);
            snprintf(file_entry, sizeof(file_entry), "%s %s %ld bytes\n", directory_name, directory_entry->d_name, entry_stat.st_size);
#else
            snprintf(file_entry, sizeof(file_entry), "%s %s %ld bytes\n", realpath(directory_entry_name, NULL), directory_entry->d_name, entry_stat.st_size);
#endif
            fputs(file_entry, output_file);
        }

        directory_entry = readdir(directory);
    }

    closedir(directory);
    return files_seen;
}

int main(int argc, char const *argv[])
{
    const char *path = argv[1];
    const int min_size = atoi(argv[2]);
    const int max_size = atoi(argv[3]);
    FILE *output_file = fopen(argv[4], "w");

    if (output_file == NULL)
    {
        printf("Something went wrong\n");
        return 1;
    }

    int files_seen = traverse_directory(path, min_size, max_size, output_file);

    fclose(output_file);

    printf("%d\n", files_seen);

    return 0;
}