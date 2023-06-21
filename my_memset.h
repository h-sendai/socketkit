/* If we use glibc 2.25 or newer, we can use explicit_bzero() */
#ifndef _MY_MEMSET
#define _MY_MEMSET 1

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern void *my_memset(void *s, int c, size_t n);

#endif
