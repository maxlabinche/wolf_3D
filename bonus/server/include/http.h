/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** print a character
*/
#ifndef SOCKET_H
    #define SOCKET_H
    #define PORT 8070
    #define MAX_EVENTS 1024
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include "game.h"
    #include <stdbool.h>
typedef struct {
    int sizesock;
    int sd;
    int bindo;
    int listo;
    struct epoll_event events[MAX_EVENTS];
    int epfd;
    struct sockaddr_in *network;
    users_t *users;
    int user_count;
    int socket_count;
} server_t;
void init_server(server_t *server);
void all_sockets(server_t *server);
int create_epollo(int sd);
int create_socket(struct sockaddr_in *network);
int write_in_socket(int accepto, char resp[]);
int all_sockets_detected(server_t *server, int i);
void all_sockets(server_t *server);
int setup_nonblock(int fd);
int create_bind(int sd, struct sockaddr_in *network);
int create_listen(int sd);
int accept_connection(int sd,
    struct sockaddr_in *network, int sizesock);
int handle_new_connection(server_t *server, int i);
void process_client_data(server_t *server,
    int client_fd, char *buffer, ssize_t bytes_read);
void send_user_list_to_client(server_t *server, int client_fd);
void handle_client_disconnection(server_t *server, int client_fd);
int handle_client_event(server_t *server, int client_fd);
int get_index_from_fd(int fd, server_t *server);
void clean_users(server_t *server);
int get_index_from_socket(int fd, server_t *server);
void send_updates_to_all_clients(server_t *server);
void send_update_index_to_all_clients(server_t *server, int index);
void remove_dead_users(server_t *server);
#endif
