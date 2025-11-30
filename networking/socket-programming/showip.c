// showip.c
// Yanked from : https://www.beej.us/guide/bgnet/source/examples/showip.c/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if(argc != 2) {
        fprintf(stderr, "Usage: showip hostname\n");
        return 1;
    }
    
    // for sin_zero from sockaddr_in
    memset(&hints, 0, sizeof hints);
    printf("DEBUG: %d\n", hints.ai_socktype);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // where the magic happens
    // getaddrinfo returns one or more addrinfo structs, which includes the ipv4
    // and ipv6 addresses of the given node (argv[1]) and service (NULL). if
    // service is NULL, then the port number of the returned socket addresses
    // will be left uninitialized.
    status = getaddrinfo(argv[1], NULL, &hints, &res);

    if(status != 0) { // if not zero, then doesn't exist
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }

    // int argv_size = sizeof &argv / sizeof *argv[0];

    // printf("argv_size : %d\n", argv_size);

    // for(int i = 0; i < argv_size; i++) {
    //     printf("argv[%d] : %s\n", i, argv[i]);
    // }
    // printf("res : %s\n", (char *)res);

    printf("IP address(es) of %s:\n\n", argv[1]);

    for(p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;

        if(p->ai_family == AF_INET) {
            ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else {
            ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
    }
    freeaddrinfo(res);

    return 0;
}
