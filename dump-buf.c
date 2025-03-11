#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int dump_buf(char *buf, int buflen)
{
    int n_lines = buflen / 16;

    for (int l = 0; l < n_lines; ++l) {
        for (int i = 0; i < 16; ++i) {
            // print hex value
            if (i == 0) {
                printf("%02x", (unsigned char) buf[16*l + i]);
            }
            else {
                printf(" %02x", (unsigned char) buf[16*l + i]);
            }
        }

        printf(" ");

        for (int i = 0; i < 16; ++i) {
            // print ascii char if printable
            if (isprint(buf[16*l + i])) {
                printf("%c", buf[16*l + i]);
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
                
    int n_rest_elem = buflen - 16*n_lines;
    if (n_rest_elem > 0) {
        for (int i = 16*n_lines; i < buflen; ++i) {
            // print hex value
            if (i == 16*n_lines) {
                printf("%02x", (unsigned char) buf[i]);
            }
            else {
                printf(" %02x", (unsigned char) buf[i]);
            }
        }
        for (int i = 0; i <= (3*16) - 3*n_rest_elem; ++i) {
            printf(" ");
        }
        for (int i = 16*n_lines; i < buflen; ++i) {
            // print ascii char if printable
            if (isprint(buf[i])) {
                printf("%c", buf[i]);
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }

    return 0;
}

#if 0
int main(int argc, char *argv[])
{
    char buf[256];

    for (int i = 0; i < sizeof(buf); ++i) {
        buf[i] = i;
    }

    dump_buf(buf, sizeof(buf));
    return 0;
}
#endif
