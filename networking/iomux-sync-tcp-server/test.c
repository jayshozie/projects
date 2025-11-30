#include <stdio.h>
#include <poll.h>

int main(void)
{
    struct pollfd pfds[1];
    pfds[0].fd = 0; // stdin
    pfds[0].events = POLLIN; // when to read

    int num_events = poll(pfds, 1, 5000);
    if(num_events == 0) {
        printf("timeout\n");
        printf("%d\n%d\n", pfds[0].events, pfds[0].revents);
    }
    else {
        int pollin_happened = pfds[0].revents & POLLIN;
        if(pollin_happened) {
            printf("%d ready to read\n", pfds[0].fd);
            printf("%d\n%d\n", pfds[0].events, pfds[0].revents);
        }
        else {
            printf("err: unexpected event %d\n", pfds[0].revents);
            printf("%d\n%d\n", pfds[0].events, pfds[0].revents);
        }

    }
    return 0;
}
