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


/*
 * man proc(5)
 * /proc/[pid]/statm
 *  Provides information about memory usage, measured in pages.  The columns are:
 *
 *  size       (1) total program size
 *             (same as VmSize in /proc/[pid]/status)
 *  resident   (2) resident set size
 *             (same as VmRSS in /proc/[pid]/status)
 *  share      (3) shared pages (i.e., backed by a file)
 *  text       (4) text (code)
 *  lib        (5) library (unused in Linux 2.6)
 *  data       (6) data + stack
 *  dt         (7) dirty pages (unused in Linux 2.6)
 */

size_t get_rss_kb()
{
    int debug = 0;
    FILE *fp = fopen("/proc/self/statm", "r");
    if (fp == NULL) {   
        warn("fopen() in get_rss_kb()");
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    size_t n = getline(&line, &len, fp);
    if (n < 0) {
        warn("getline() in get_rss_kb()");
        return -1;
    }

    line[n - 1] = '\0';
    char *size __attribute__((unused)) = strtok(line, " ");
    char *resident = strtok(NULL, " ");
    if (debug) {
        fprintf(stderr, "%s\n", resident);
    }
    // char *share    = strtok(NULL, " ");
    // char *text     = strtok(NULL, " ");
    // char *lib      = strtok(NULL, " ");
    // char *data     = strtok(NULL, " ");
    // char *dt       = strtok(NULL, " ");
    
    size_t rss    = strtol(resident, NULL, 0);
    size_t rss_kb = rss*4; /* 4kB per one page */
    
    return rss_kb;
}

#if 0
int main(int argc, char *argv[])
{
    size_t bufsize = 8*1024*1024;
    char *buf = malloc(bufsize);

    size_t k_bytes = get_rss_kb();
    printf("RSS: %ld kB\n", k_bytes);

    memset(buf, 'X', bufsize);
    k_bytes = get_rss_kb();
    printf("RSS: %ld kB\n", k_bytes);

    return 0;
}
#endif
