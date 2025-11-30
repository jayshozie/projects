// #include <stdint.h>     for uintxx_t
// #include <stdlib.h>     for u_intxx_t
// #include <sys/socket.h> for socket related stuff

struct sockaddr {
    unsigned short sa_family_t; // address family, AF_x
    char           sa_data[14]; // 14 bytes of protocol address
};

struct in_addr { // --- IPv4 ONLY !!! ---
    // uint32_t from stint.h
    uint32_t s_addr; // that's a 32-bit int (4 bytes)
};

struct in6_addr { // --- IPv6 ONLY !!! ---
    unsigned char s6_addr[16]; // IPv6 address
};

struct sockaddr_in { // --- IPv4 ONLY !!! ---
    short int sin_family; // address family, AF_INET
    unsigned short int sin_port; // port num
    // sin_port must be in Network Byte Order, use htons()
    struct in_addr sin_addr; // internet address
    unsigned char sin_zero[8]; // same size as struct sockaddr
    // sin_zero should be set to all zeros with the function memset()
};

struct sockaddr_in6 { // --- IPv6 ONLY !!! ---
    // u_intxx_t from stdlib.h
    u_int16_t sin6_family; // address family, AF_INET6
    u_int16_t sin6_port; // port, Network Byte Order
    u_int32_t sin6_flowinto; // IPv6 flow information
    struct in6_addr sin6_addr; // IPv6 address
    u_int32_t sin6_scope_id; // Scope ID
};

/**
 * definition of addrinfo
 */
struct addrinfo {
    // ai_ stands for address info (addrinfo)
    int ai_flags;             // AI_PASSIVE, AI_CANONNAME, etc.
    int ai_family;            // AF_INET, AF_INET6, AF_UNSPEC
    int ai_socktype;          // SOCK_STREAM, SOCK_DGRAM
    int ai_protocol;          // use 0 for "any"
    // size_t from sys/types.h
    size_t ai_addrlen;        // size of ai_addr in bytes
    struct sockaddr *ai_addr; // struct sockaddr_in or _in6
    char *ai_canonname;       // full canonical hostname

    struct addrinfo *ai_next; // linked list, ptr to next node
};

typedef struct {
    // ...
} sa_family_t; // implementation doesn't matter

struct sockaddr_storage {
    sa_family_t ss_family;

    // implementation specific paddings
    // ...
    // ...
};

/**
 * To convert string IP addresses to their binary representations:
// from arpa/inet.h
 * inet_pton(int af, const char *restricct src, void *restrict dst);
 * af  : converts src into a network address structure in the af address family
 * src : points to a character string containing an IPv4/v6 network address in
 *       dotted decimal format
 * dst : copied into network address structure
 */

// it helps to set up struct s.
int getaddrinfo(const char *node, // hostname, or an IP address
                const char *service, // can be a port number, or a specific service like http, ftp, etc.
                const struct addrinfo *hints, // points to a struct already filled out
                struct addrinfo **res); // returns a pointer to a linked-list res of results
// return 0 if succeeds.


// To get struct sockaddr_in or _in6 from IP address
struct sockaddr_in sa;
struct sockaddr_in6 sa6;
// from arpa/inet.h
inet_pton(AF_INET, "the.ipv4.addr.str", &(sa.sin_addr));
inet_pton(AF_INET6, "the:ipv6:addr::str", &(sa6.sin6_addr));

// To get IP address from struct in_addr or in6_ for IPv6
char ip4[INET_ADDRSTRLEN]; // space to hold the IPv4 string
struct sockaddr_in sa;     // pretend this is loaded with something
// from arpa/inet.h
inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
// from stdio.h
printf("The IPv4 address is: %s\n", ip4);

// included in sys/socket.h
// syscall to create an endpoint for communication, returns a file descriptor
// that refers to that endpoint.
int socket(int domain, int type, int protocol);
/**
 * domain   : PF_INET or PF_INET6
 * type     : SOCK_STREAM, SOCK_DGRAM, SOCK_RAW, etc.
 * protocol : AF_INET, AF_INET6, AF_UNIX, etc.
 */

// included in sys/socket.h
// syscall to assign the address specified by addr to the socket referred to by
// the file descriptor sockfd. addrlen specifies the size, in bytes, of the
// address structure pointed to by addr. a.k.a. assigning a name to a socket
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
/**
 * sockfd  : file descriptor for the socket
 * addr    : address structure pointer
 * addrlen : size of the address structure pointed by addr, in BYTES
 */
