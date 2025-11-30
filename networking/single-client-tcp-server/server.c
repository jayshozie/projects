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
    // basic tcp server
    char *ip = "127.0.0.1";
    int PORT = 8080;
    int BACKLOG = 20;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    char exit_arr[1024];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_sock < 0) {
        perror("[-] Socket error.\n");
        exit(1);
    }
    printf("[+] TCP server socket created.\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(n < 0) {
        perror("[-] Bind error.\n");
        exit(1);
    }
    printf("[+] Bind to the port number: %d\n", server_addr.sin_port);

    listen(server_sock, BACKLOG);
    printf("Listening...\n");

    addr_size = sizeof(client_addr);
    client_sock
        = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
    printf("[+] Client connected.\n");

    // setup exit_arr
    memset(&exit_arr, 0, sizeof(exit_arr));
    strcpy(exit_arr, "disconnect");

    printf("Use the command disconnect to close the server.\n");
    while(1) {
        // RECEIVE
        memset(&buffer, 0, sizeof(buffer));
        recv(client_sock, buffer, sizeof(buffer), 0);
        if(is_same(buffer, exit_arr) == true) {
            printf("[+] Client disconnected.\n");
            break;
        }
        printf("Client: %s", buffer);

        // SEND
        memset(&buffer, 0, sizeof(buffer));
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(client_sock, buffer, strlen(buffer), 0);
        if(is_same(buffer, exit_arr) == true) {
            printf("[+] Server closed.\n");
            break;
        }
    }
    close(client_sock);
    return 0;
}
