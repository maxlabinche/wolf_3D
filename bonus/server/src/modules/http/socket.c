/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** print a character
*/
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include "../../../include/http.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int create_socket(struct sockaddr_in *network)
{
    int sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd == -1) {
        perror("webserver (socket)");
        exit(84);
    }
    network->sin_family = AF_INET;
    network->sin_port = htons(PORT);
    network->sin_addr.s_addr = htonl(INADDR_ANY);
    return sd;
}

int write_in_socket(int accepto, char resp[])
{
    int writo = write(accepto, resp, strlen(resp));

    if (writo == -1) {
        perror("webserver (write)");
        close(accepto);
        return -1;
    }
    return writo;
}

int get_index_from_fd(int fd, server_t *server)
{
    for (int i = 0; i < server->user_count; i++) {
        if (server->users[i].fd == fd) {
            return i;
        }
    }
    return -1;
}

int get_index_from_socket(int fd, server_t *server)
{
    for (int i = 0; i < server->user_count; i++) {
        if (server->users[i].socket == fd && server->users[i].type == 0) {
            return i;
        }
    }
    return -1;
}

int all_sockets_detected(server_t *server, int i)
{
    if (server->events[i].data.fd == server->sd) {
        handle_new_connection(server, i);
    } else {
        handle_client_event(server, server->events[i].data.fd);
    }
    send_updates_to_all_clients(server);
}

void all_sockets(server_t *server)
{
    int nfds = 0;

    for (;;) {
        nfds = epoll_wait(server->epfd, server->events, MAX_EVENTS, -1);
        for (int i = 0; i < nfds; i++) {
            all_sockets_detected(server, i);
        }
    }
    close(server->epfd);
    close(server->sd);
}
