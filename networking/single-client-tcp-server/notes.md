# Notes for TCP Only

## Socket *BOTH*
Both the server and the client needs to create a socket. This creates a
communication endpoint. `<sys/socket.h>` `socket()` in C.

## Binding to an Address *SERVER*
The server needs to assign an IP address and a port number to its socket,
`bind()` in C. The server will listen to that port.

## Listening to Connections *SERVER*
The server needs to start listening to its socket, `listen()` in C. This allows
it to queue incoming connection requests. Backlog must be specified. Just create
an MAX_BACKLOG uint8_t variable with value 255.

## Connecting to the Server *CLIENT*
The client needs to establish a connection to the server, `connect()` in C. It
specifies the IP and Port of the server's socket.

## Sending and Receiving Data *BOTH*
Once the connection is established, both the client and the server can exchange
data using `send()` and `recv()` methods for TCP.

## Closing the Socket *BOTH*
After the communication is complete, sockets are closed with `close()` to free
up resources.

# Requirements

## From C STDLIB

1. **<netinet/in.h>:** Easier programming basically, it defines stuff like
`in_port_t` which is equivalent to `uint16_t`, and `in_addr_t` which is
equivalent to `uint32_t`.

2. **<stdio.h>:** Well, standard input/output. Pretty self-explanatory.

3. **<stdlib.h>:** Generally, memory management.

3. **<sys/socket.h>:** Socket stuff itself. All struct and functions are defined
here.

4. **<unistd.h>:** POSIX (CLI) stuff

5. **<string.h>:** Self-explanatory.

# Didn't Understand

~1. `backlog`~

# Definitions

1. **Backlog:** the maximum number of queued connections the socket will hold.

2. **Loopback Address:** 127.0.0.1 for IPv4 and ::1
(0000:0000:0000:0000:0000:0000:0000:0001) for IPv6.

3. IP Address: 32-bit (IPv4) or 128-bit (IPv6) address of the network

4. Port Number: 16-bit number of local address for the connection.

5. Byte Order: Little Endian and Big Endian; x86 => LE

    | Function  | Description                 |
    |:----------|----------------------------:|
    | `htons()` | `h`ost to `n`etwork `s`hort |
    | `htonl()` |  `h`ost to `n`etwork `l`ong |
    | `ntohs()` | `n`etwork to `h`ost `s`hort |
    | `ntohl()` |  `n`etwork to `h`ost `l`ong |

# TODO

- [ ] `server.c`
    - [ ] Socket Creation
    - [ ] Address Binding (IP/PORT)
    - [ ] Listening Connection (Don't forget `backlog`.)
    - [ ] Send/Receive Data (Must be bytes)
    - [ ] Close Socket (Clean coding)

- [ ] `client.c`
    - [ ] Socket Creation
    - [ ] Server Connection (IP/PORT Specified)
    - [ ] Send/Receive Data (Must be bytes)
    - [ ] Close Socket (Clean coding)
