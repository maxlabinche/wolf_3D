/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** events
*/

#include "palwish.h"
#include <math.h>

void handle_pause(game_t *game, input_t *input)
{
    if (input->keys[sfKeyP]) {
        game->paused = !game->paused;
        if (game->paused) {
            sfRenderWindow_setMouseCursorGrabbed(game->window, sfFalse);
            sfRenderWindow_setMouseCursorVisible(game->window, sfTrue);
        } else {
            sfRenderWindow_setMouseCursorGrabbed(game->window, sfTrue);
            sfRenderWindow_setMouseCursorVisible(game->window, sfFalse);
        }
    }
}

void handle_common(game_t *game, input_t *input)
{
    sfTime elapsed;

    elapsed = sfClock_getElapsedTime(game->common);
    if (sfTime_asSeconds(elapsed) >= 0.1) {
        handle_pause(game, input);
        sfClock_restart(game->common);
    }
}
