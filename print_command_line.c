#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int print_command_line(int argc, char *argv[])
{
    printf("#");

    for (int i = 0; i < argc; ++i) {
        if (strchr(argv[i], ' ') == NULL) {
            printf(" %s", argv[i]);
        }
        else {
            printf(" \"%s\"", argv[i]);
        }
    }

    printf("\n");
    
    return 0;
}
