/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"
#include <pthread.h>

void update_network(game_t *game, player_t *player)
{
    pthread_t tid;
    thread_data_t *data = malloc(sizeof(thread_data_t));

    if (!data)
        exit(84);
    data->player = player;
    data->game = game;
    pthread_create(&tid, NULL, (void *)actualise_data, (void *)data);
    pthread_join(tid, NULL);
    free(data);
}

void go_vibre_treads(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, (void *)vibrate, (void *)200);
}

void init_game_bonus(game_t *game)
{
    game->offline = false;
    return;
}
