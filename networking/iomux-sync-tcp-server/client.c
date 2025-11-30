#define _POSIX_C_SOURCE 200809L
#include "is_same.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

int main(void)
{
    char *ip = "127.0.0.1";
    int PORT = 8080;

    int sock;
    int connection;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    char exit_arr[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0) {
        perror("[-] Socket error.\n");
        exit(1);
    }
    printf("[+] TCP server socket created.\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = PORT;
    addr.sin_addr.s_addr = inet_addr(ip);

    connection = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if(connection < 0) {
        perror("[-] Couldn't connect.\n");
        exit(1);
    }
    printf("[+] Connected successfully.\n");

    // setup exit_arr
    memset(&exit_arr, 0, sizeof(exit_arr));
    strcpy(exit_arr, "disconnect");

    printf("Use the command disconnect to disconnect from the server.\n");
    while(1) {
        // SEND
        memset(&buffer, 0, sizeof(buffer));
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(sock, buffer, strlen(buffer), 0);
        if(is_same(buffer, exit_arr) == true) {
            printf("[+] Disconnected.\n");
            break;
        }

        // RECEIVE
        memset(&buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        if(is_same(buffer, exit_arr) == true) {
            printf("[+] Server closed.\n");
            break;
        }
        printf("Server: %s", buffer);
    }
    close(sock);
    return 0;
}
