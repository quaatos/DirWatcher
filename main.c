#include <stdio.h>
#include <dirent.h>
#include <time.h>

int prevFilecount = 0;
int filecount = 0;

int main(void) {
    for(;;) {
        filecount = CountMembers("Path/To/Directory");
        if (filecount > prevFilecount) system("curl -d \"File added!\" ntfy.sh/subject"); //Send notification to phone using the ntfy.sh app

        prevFilecount = filecount;
        filecount = 0;
        sleep(1);
    }

    return 0;
}

int CountMembers(char *path) {
    DIR *directory;
    struct dirent *entry;

    directory = opendir(path);

    if (directory == NULL)
    {
        printf("Error opening directory");
        return 1;
    }

    while((entry = readdir(directory)) != NULL)
    {
        if (entry->d_type == DT_REG) //check if the member is of type "file"
        {
            filecount++;
        }
        //if you want to check for new directory's instead of files. Change "DT_REG" to "DT_DIR"
    }

    return filecount;
}

