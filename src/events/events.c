/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** events
*/

#include "palwish.h"
#include <math.h>

void handle_event(game_t *game,
    sfEvent event, input_t *input, player_t *player)
{
    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed
            || (event.type == sfEvtKeyPressed
            && event.key.code == sfKeyEscape)) {
            sfRenderWindow_close(game->window);
        }
        if (event.type == sfEvtKeyPressed && event.key.code >= 0
            && event.key.code < NUM_KEYS) {
            input->keys[event.key.code] = true;
        }
        if (event.type == sfEvtKeyReleased && event.key.code >= 0
            && event.key.code < NUM_KEYS) {
            input->keys[event.key.code] = false;
        }
    }
    handle_event_manette(input, player);
}
