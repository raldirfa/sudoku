#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_operations.h"

// From https://stackoverflow.com/a/3463793
int read_file(int arrayToFill[], char path[])
{
    FILE *file;
    int c;
    int i = 0;

    file = fopen(path, "r");
    if (file) {
        while ((c = getc(file)) != EOF){
            if (c != 10)
            {
                arrayToFill[i] = c - 48;
                i++;
            }
        }
        fclose(file);
        return 0;
    }
    return -1;
}
