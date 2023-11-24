#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }
    
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s\n", line);
        free(line); // Don't forget to free the line after using it
    }

    close(fd);

    return 0;
}

