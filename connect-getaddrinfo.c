#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int connect_tcp(char *remote_host, char *port)
{
    struct addrinfo hints;
    struct addrinfo *result;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = 0;
    hints.ai_protocol = 0;
    
    int s = getaddrinfo(remote_host, port, &hints, &result);
    if (s != 0) {
        warnx("getaddrinfo: %s", gai_strerror(s));
        return -1;
    }
    
    int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sockfd < 0) {
        warn("socket");
        return -1;
    }

    if (connect(sockfd, result->ai_addr, result->ai_addrlen) < 0) {
        warn("connect");
        return -1;
    }

    freeaddrinfo(result);

    return sockfd;
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: sample remote_host port\n");
        exit(1);
    }

    char *remote_host = argv[1];
    char *port        = argv[2];

    int sockfd = connect_tcp(remote_host, port);
    if (sockfd < 0) {
        errx(1, "connect_tcp error");
    }

    close(sockfd);

}
