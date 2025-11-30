/*
 * Multi-Person Chatroom via TCP
 */
#include "is_same.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ever (;;)
#define PORT "8080"
#define IP   "127.0.0.1"

/*
 * Convert socket to IP address string.
 * addr : struct sockaddr_in or struct sockaddr_in6
 * dst  : destination string (char*)
 * size : size of dst (size_t)
 */
const char *inet_ntop2(void *addr, char *dst, size_t size)
{
    struct sockaddr_storage *sas = addr;
    struct sockaddr_in *sa4;
    struct sockaddr_in6 *sa6;
    void *src;

    switch(sas->ss_family) {
    case AF_INET:
        sa4 = addr;
        src = &(sa4->sin_addr);
    case AF_INET6:
        sa6 = addr;
        src = &(sa6->sin6_addr);
    default:
        return NULL;
    }

    return inet_ntop(sas->ss_family, src, dst, size);
}

/*
 * Returning a listening socket.
 */
int get_listener_socket(void)
{
    int yes = 1; // for setsockopt() SO_REUSEADDR, below
    int listener, rv, n; // listening socket descriptor

    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    rv = getaddrinfo(NULL, PORT, &hints, &ai);
    if(rv != 0) {
        fprintf(stderr, "[Chatroom] ERR: %s\n", gai_strerror(rv));
        exit(1);
    }
    for(p = ai; p != NULL; p = p->ai_next) {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(listener < 0) { continue; }
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if(bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
            close(listener);
            continue;
        }

        break;
    }

    if(p == NULL) { // if we got here, we didn't get bound
        return -1;
    }

    freeaddrinfo(ai);

    if(listen(listener, 100) == -1) { // listen
        return -1;
    }
    return listener;
}

/*
 * Add a new file descriptor to the set.
 * pfds     : array of pollfd structs (struct pollfd **)
 * newfd    : new file descriptor (int)
 * fd_count : size of pfds (int *)
 * fd_size  : size of an fd (int *)
 */
void add_to_pfds(struct pollfd **pfds, int newfd, int *fd_count, int *fd_size)
{
    // add space if space not enough
    if(*fd_count == *fd_size) {
        *fd_size *= 2; // double
        *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN;
    (*pfds)[*fd_count].revents = 0;

    (*fd_count)++;
}

/*
 * Remove a file descriptor at a given index from the set.
 * pfds     : array of struct pollfd's (struct pollfd [])
 * i        : index of the fd to delete (int)
 * fd_count : length of pfds (int *)
 */
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    pfds[i] = pfds[*fd_count - 1]; // copy from end to the deleted place
    (*fd_count)--; // decrement
}

void handle_new_connection(int listener, int *fd_count, int *fd_size,
                           struct pollfd **pfds)
{
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;
    int newfd;
    char remoteIP[INET6_ADDRSTRLEN];

    addrlen = sizeof(remoteIP);
    newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

    if(newfd < 0) {
        perror("[Chatroom] ERR: Couldn't accept.");
    }
    else {
        add_to_pfds(pfds, newfd, fd_count, fd_size);
    }
}

int main(void)
{
    int listener;

    // room for 50 connections
    int fd_size = 50;
    int fd_count = 0;
    struct pollfd *pfds = malloc(sizeof(*pfds) * fd_size);

    listener = get_listener_socket();
    if(listener < 0) {
        fprintf(stderr, "[Chatroom] ERR: Getting listening socket.\n");
        exit(1);
    }
    printf("[Chatroom] Chatroom created.\nSize: %d.\n", fd_size);

    pfds[0].fd = listener;
    pfds[0].events = POLLIN;
    fd_count++; // for listener

    puts("[Chatroom] Waiting for connections...\n");

    for
        ever
        {
            int poll_count = poll(pfds, fd_count, -1);
            if(poll_count < 0) {
                fprintf(stderr, "[Chatroom] ERR: Poll");
                exit(1);
            }

            process_connections(listener, &fd_count, &fd_size, &pfds);
        }

    free(pfds);
    return 0;
}
