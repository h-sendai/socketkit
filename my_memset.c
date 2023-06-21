/* If we use glibc 2.25 or newer, we can use explicit_bzero() */
#include <stdio.h>

void *my_memset(void *s, int c, size_t n)
{
    volatile unsigned char *p = s;
    for (int i = 0; i < n; ++i) {
        p[i] = c;
    }
    return s;
}
