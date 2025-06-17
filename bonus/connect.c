/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include "palwish.h"
#include <pthread.h>
#include <fcntl.h>

static void set_socket_non_blocking(int socket_fd)
{
    int flags = fcntl(socket_fd, F_GETFL, 0);

    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }
    if (fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }
}

void connection(game_t *game)
{
    struct sockaddr_in server_addr;

    if (game->offline == true)
        return;
    game->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (game->socket == -1)
        exit(EXIT_FAILURE);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        close(game->socket);
        exit(EXIT_FAILURE);
    }
    if (connect(game->socket,
        (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        close(game->socket);
        exit(EXIT_FAILURE);
    }
    set_socket_non_blocking(game->socket);
    printf("Connecté au serveur %s:%d\n", SERVER_IP, SERVER_PORT);
}

void send_player_data(game_t *game, player_t *player)
{
    char buffer[512];

    snprintf(buffer, sizeof(buffer), "%d/%f/%f/%f/%d\n",
    game->whoami, player->x, player->y, player->health, 0);
    if (send(game->socket, buffer, strlen(buffer), 0) == -1)
        fprintf(stderr, "Erreur lors de l'envoi des données\n");
}

char *prepare_data(game_t *game, int j)
{
    char user_data[256];

    if (game->objects[j].origine == 0) {
        snprintf(user_data, sizeof(user_data),
        "%d/%f/%d\n", game->objects[j].user,
            game->objects[j].health, game->objects[j].type);
    } else
        snprintf(user_data, sizeof(user_data),
        "%d/%f/%f/%f/%d\n",
            game->objects[j].user, game->objects[j].x,
            game->objects[j].y, game->objects[j].health,
            game->objects[j].type);
    return strdup(user_data);
}

void send_all_users_data(game_t *game)
{
    char all_users_data[1024] = {0};
    char *user_data;

    game->send_object = 0;
    for (int j = 0; j < game->object_count; j++) {
        if (game->objects[j].has_changed == false)
            continue;
        game->send_object++;
        game->objects[j].has_changed = false;
        user_data = prepare_data(game, j);
        strncat(all_users_data, user_data,
            sizeof(all_users_data) - strlen(all_users_data) - 1);
    }
    if (send(game->socket, all_users_data,
        strlen(all_users_data), 0) == -1)
        fprintf(stderr, "Erreur lors de l'envoi des données\n");
}

static void process_received_line(game_t *game,
    const char *line, player_t *player)
{
    network_user_t *netu = malloc(sizeof(network_user_t));

    if (!netu)
        exit(84);
    if (sscanf(line, "%d/%lf/%lf/%lf/%d",
        &netu->user, &netu->x, &netu->y, &netu->life, &netu->type) == 5
        && netu->user != game->whoami) {
        create_object_or_move(game, netu);
    } else if (netu->user == game->whoami && player->health > netu->life) {
        player->health = netu->life;
        return;
    }
}

static void receive_and_process_data(game_t *game, player_t *player)
{
    char buffer[512];
    char *line;
    ssize_t bytes_received;

    game->receive_object = 0;
    bytes_received = recv(game->socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        line = strtok(buffer, "\n");
        while (line != NULL) {
            process_received_line(game, line, player);
            game->receive_object++;
            line = strtok(NULL, "\n");
        }
    }
}

static double get_time(void)
{
    struct timespec ts;
    double milliseconds;

    clock_gettime(CLOCK_REALTIME, &ts);
    milliseconds = (ts.tv_sec * 1000.0)
    + (ts.tv_nsec / 1000000.0);
    return milliseconds;
}

void actualise_data(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    double start_time = get_time();
    double elapsed_time = 0.0;

    if (data->game->offline == true)
        return;
    send_player_data(data->game, data->player);
    send_all_users_data(data->game);
    receive_and_process_data(data->game, data->player);
    elapsed_time = get_time() - start_time;
    data->game->latency = elapsed_time;
    remove_dead_objects(data->game);
}
