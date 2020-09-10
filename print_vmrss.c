#include "print_vmrss.h"

int print_vmrss()
{
    FILE *fp = fopen("/proc/self/status", "r");
    if (fp == NULL) {
        err(1, "fopen");
    }

    char *line = NULL;
    size_t len;
    size_t n;
    while ( (n = getline(&line, &len, fp)) != -1) {
        if (strncmp(line, "VmRSS", 5) == 0) {
            fprintf(stderr, "%s", line);
            break;
        }
    }

    free(line);
    fclose(fp);

    return 0;
}
