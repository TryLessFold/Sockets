#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_IP INADDR_ANY
#define SERVER_PORT 15000
#define MAX_CLTS 10

int init_socket(int *sock, struct sockaddr_in *addr, socklen_t *size)
{
    if ((*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        return -1;
    }

    while (bind(*sock, (struct sockaddr *)addr, *size) == -1)
    {
        switch (errno)
        {
        case EADDRINUSE:
        case EACCES:
            addr->sin_port = htons(htons(addr->sin_port) + 1);
            printf("Server port: %d", ntohs(addr->sin_port));
            break;
        default:
            return -1;
        }
    }

    return 0;
}

int reg_to_select(int *sock_arr, int size, int reged)
{
    int i = -1;

    while (sock_arr[++i] == -1 && i < size);

    if (i < size)
    {
        sock_arr[i] = reged;
        return 0;
    }

    return -1;
}

int unreg_to_select(int *sock_arr, int size, int reged)
{
    int i = -1;

    while (sock_arr[++i] != reged && i < size)

    if (i < size)
    {
        sock_arr[i] = -1;
        return 0;
    }

    return -1;
}

int main()
{
    int server_sock;
    int client_socks[MAX_CLTS];

    if ()

}