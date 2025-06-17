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

void update_user_data(server_t *server, int index, float x, float y)
{
    server->users[index].x = x;
    server->users[index].y = y;
    server->users[index].life = 5;
    server->users[index].type = 0;
}

static int new_index(server_t *server)
{
    int index = server->user_count;

    server->users = realloc(server->users,
        (server->user_count + 1) * sizeof(users_t));
    server->user_count++;
    return index;
}

void parse_and_update_user(server_t *server, char *line, int client_fd)
{
    int user = 0;
    float x = 0.0f;
    float y = 0.0f;
    float life = 0;
    int index;
    int type = 0;

    if (sscanf(line, "%d/%f/%f/%f/%d",
        &user, &x, &y, &life, &type) == 5) {
        index = get_index_from_fd(user, server);
        if (index == -1) {
            if (life <= 0)
                return;
            index = new_index(server);
            if (type == 0)
                server->users[index].socket = client_fd;
            server->users[index].life = life;
        }
        server->users[index].fd = user;
        server->users[index].x = x;
        server->users[index].y = y;
        if (life >= 0 && server->users[index].life > life)
            server->users[index].life = life;
        server->users[index].type = type;
        server->users[index].updated = 1;
    } else if (sscanf(line, "%d/%f/%d",
        &user, &life, &type) == 3) {
        index = get_index_from_fd(user, server);
        if (index == -1) {
            return;
        }
        if ((life >= 0 && server->users[index].life > life && user != 0))
            server->users[index].life = life;
        server->users[index].updated = 1;
    } else {
        printf("Invalid data format: %s\n", line);
    }
}

void process_buffer_lines(server_t *server, char *buffer, int client_fd)
{
    char *line = strtok(buffer, "\n");

    while (line != NULL) {
        parse_and_update_user(server, line, client_fd);
        line = strtok(NULL, "\n");
    }
}

void process_client_data(server_t *server,
    int client_fd, char *buffer, ssize_t bytes_read)
{
    buffer[bytes_read] = '\0';
    process_buffer_lines(server, buffer, client_fd);
}

void remove_user(server_t *server, int user_fd)
{
    int index = get_index_from_fd(user_fd, server);

    if (index == -1) {
        printf("User with fd %d not found.\n", user_fd);
        return;
    }

    printf("Removing user with fd %d.\n", user_fd);

    memmove(&server->users[index], &server->users[index + 1], 
            (server->user_count - index - 1) * sizeof(users_t));

    server->user_count--;
    server->users = realloc(server->users, server->user_count * sizeof(users_t));

    if (server->user_count == 0) {
        printf("No users left, cleaning up resources.\n");
        clean_users(server);
    }
}

void remove_dead_users(server_t *server)
{
    for (int i = 0; i < server->user_count; ) {
        if (server->users[i].life == 0) {
            printf("User with fd %d has 0 or less life. Removing...\n", server->users[i].fd);
            remove_user(server, server->users[i].fd);
        } else {
            i++;
        }
    }
}

void *periodic_user_cleanup(void *arg)
{
    server_t *server = (server_t *)arg;

    while (1) {
        sleep(30);
        remove_dead_users(server);
    }
}

void send_updates_to_all_clients(server_t *server)
{
    char all_users_data[1024] = {0};
    char user_data[256];

    for (int j = 0; j < server->user_count; j++) {
        if (server->users[j].updated) {
            snprintf(user_data, sizeof(user_data),
            "%d/%f/%f/%f/%d\n",
                server->users[j].fd, server->users[j].x,
                server->users[j].y, server->users[j].life, server->users[j].type);
            strncat(all_users_data, user_data,
                sizeof(all_users_data) - strlen(all_users_data) - 1);
            server->users[j].updated = 0;
        }
    }
    for (int i = 0; i < server->user_count; i++) {
        if (server->users[i].socket && server->users[i].type == 0) {
            write_in_socket(server->users[i].socket, all_users_data);
        }
    }
    remove_dead_users(server);
}

void send_update_index_to_all_clients(server_t *server, int index)
{
    char all_users_data[1024] = {0};
    char user_data[256];

    snprintf(user_data, sizeof(user_data),
        "%d/%f/%f/%f/%d\n",
        server->users[index].fd, server->users[index].x,
        server->users[index].y, server->users[index].life, server->users[index].type);
    strncat(all_users_data, user_data,
        sizeof(all_users_data) - strlen(all_users_data) - 1);
    for (int i = 0; i < server->user_count; i++) {
        if (server->users[i].socket && server->users[i].type == 0) {
            write_in_socket(server->users[i].socket, all_users_data);
        }
    }
}

void send_user_list_to_client(server_t *server, int client_fd)
{
    char all_users_data[1024] = {0};
    char user_data[256];

    for (int j = 0; j < server->user_count; j++) {
        snprintf(user_data, sizeof(user_data),
        "%d/%f/%f/%f/%d\n",
            server->users[j].fd, server->users[j].x,
            server->users[j].y, server->users[j].life, server->users[j].type);
        strncat(all_users_data, user_data,
            sizeof(all_users_data) - strlen(all_users_data) - 1);
    }
    write_in_socket(client_fd, all_users_data);
}
