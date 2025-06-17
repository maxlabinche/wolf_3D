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

int handle_new_connection(server_t *server, int i)
{
    struct epoll_event event;
    int accepto = accept_connection(server->sd,
        server->network, server->sizesock);

    if (accepto == -1)
        return -1;
    event.events = EPOLLIN;
    event.data.fd = accepto;
    if (epoll_ctl(server->epfd, EPOLL_CTL_ADD, accepto, &event) == -1) {
        perror("webserver (epoll_ctl)");
        close(accepto);
        return -1;
    }
    server->users = realloc(
        server->users, (server->user_count + 1) * sizeof(users_t));
    server->socket_count++;
    printf("Nouvelle connexion acceptée : socket %d\n", accepto);
    send_user_list_to_client(server, accepto);
    return 0;
}

void clean_users(server_t *server)
{
    for (int i = 0; i < server->user_count; i++) {
        server->users[i].life = 0;
        server->users[i].updated = 1;
    }
    remove_dead_users(server);
}

void clean_server(server_t *server)
{
    server->socket_count = 0;
    server->user_count = 0;
    server->sizesock = 0;
}

void handle_client_disconnection(server_t *server, int client_fd)
{
    int index = get_index_from_socket(client_fd, server);
    printf("Connexion fermée par le client : socket %d\n", client_fd);
    if (index != -1) {
        server->users[index].life = 0;
        server->users[index].socket = -1;
        send_update_index_to_all_clients(server, index);
    }
    server->socket_count--;
    printf("Index de l'utilisateur : %d\n", server->socket_count);
    if (server->socket_count <= 0) {
        printf("Aucun utilisateur connecté, nettoyage des ressources.\n");
        clean_users(server);
        clean_server(server);
    }
    printf("Number of users: %d\n", server->socket_count);
    close(client_fd);
    epoll_ctl(server->epfd, EPOLL_CTL_DEL, client_fd, NULL);
}

int handle_client_event(server_t *server, int client_fd)
{
    char buffer[1024];
    ssize_t bytes_read;

    bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    while (bytes_read > 0) {
        process_client_data(server, client_fd, buffer, bytes_read);
        bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    }
    if (bytes_read == 0) {
        handle_client_disconnection(server, client_fd);
    } else if (bytes_read == -1 && errno != EAGAIN) {
        perror("Erreur lors de la lecture des données");
        handle_client_disconnection(server, client_fd);
    }
    return 0;
}
