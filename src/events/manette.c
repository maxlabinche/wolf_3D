/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** events
*/

#include "palwish.h"
#include <math.h>

static void handle_joysticsk_rotation_x(
    player_t *player, float x_axis)
{
    if (fabs(x_axis) > 15) {
        player->angle += x_axis * 0.0005;
        if (player->angle < 0)
            player->angle += 2 * M_PI;
        if (player->angle > 2 * M_PI)
            player->angle -= 2 * M_PI;
    }
}

void handle_joysticsk_rotation(player_t *player)
{
    float x_axis = 0;

    if (!sfJoystick_isConnected(0))
        return;
    x_axis = sfJoystick_getAxisPosition(0, sfJoystickU);
    handle_joysticsk_rotation_x(player, x_axis);
}

static void handle_joysticsk_movement_x(player_t *player,
    float x_axis, float *new_x, float *new_y)
{
    if (fabs(x_axis) > 15) {
        *new_x += x_axis * 0.000008 * player->speed *
        TILE_SIZE * cos(player->angle + (M_PI / 2));
        *new_y += x_axis * 0.000008 * player->speed *
        TILE_SIZE * sin(player->angle + (M_PI / 2));
    }
}

static void handle_joysticsk_movement_y(player_t *player,
    float y_axis, float *new_x, float *new_y)
{
    if (fabs(y_axis) > 15) {
        *new_x -= y_axis * 0.000008 * player->speed *
        TILE_SIZE * cos(player->angle);
        *new_y -= y_axis * 0.000008 * player->speed *
        TILE_SIZE * sin(player->angle);
    }
}

void handle_joysticsk_movement(game_t *game, player_t *player)
{
    float x_axis = 0;
    float y_axis = 0;
    float new_x;
    float new_y;

    if (sfJoystick_isConnected(0)) {
        x_axis = sfJoystick_getAxisPosition(0, sfJoystickX);
        y_axis = sfJoystick_getAxisPosition(0, sfJoystickY);
        new_x = player->x;
        new_y = player->y;
        handle_joysticsk_movement_x(player, x_axis, &new_x, &new_y);
        handle_joysticsk_movement_y(player, y_axis, &new_x, &new_y);
        if (!is_wall((int)(new_x), (int)player->y, game->map)) {
            player->x = new_x;
        }
        if (!is_wall((int)player->x, (int)(new_y), game->map)) {
            player->y = new_y;
        }
    }
}

void handle_joysticsk(game_t *game, player_t *player)
{
    handle_joysticsk_rotation(player);
    handle_joysticsk_movement(game, player);
}

void handle_event_manette(input_t *input, player_t *player)
{
    float x_axis = sfJoystick_getAxisPosition(0, sfJoystickR);

    if (x_axis > 15 && player->weapon[player->actual_weapon].munitions > 0
        && player->reloading == false) {
        input->keys[sfKeySpace] = true;
        go_vibre_treads();
    } else {
        input->keys[sfKeySpace] = false;
    }
    if (sfJoystick_isButtonPressed(0, 4)) {
        input->keys[sfKeyR] = true;
    } else if (!sfKeyboard_isKeyPressed(sfKeyR)) {
        input->keys[sfKeyR] = false;
    }
    if (sfJoystick_isButtonPressed(0, 9)) {
        input->keys[sfKeyLShift] = true;
    } else if (!sfKeyboard_isKeyPressed(sfKeyLShift)) {
        input->keys[sfKeyLShift] = false;
    }
}
