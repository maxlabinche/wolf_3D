/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** events
*/

#include "palwish.h"
#include <math.h>

static void move_player(player_t *player,
    input_t *input, int **map, game_t *game)
{
    float movement_speed = player->speed * game->delta_time * 10;
    float new_x = player->x;
    float new_y = player->y;

    if (input->keys[sfKeyUp] || input->keys[sfKeyZ]) {
        new_x += movement_speed * cos(player->angle);
        new_y += movement_speed * sin(player->angle);
    }
    if (input->keys[sfKeyDown] || input->keys[sfKeyS]) {
        new_x -= movement_speed * cos(player->angle);
        new_y -= movement_speed * sin(player->angle);
    }
    if (!is_wall((int)(new_x), (int)player->y, map))
        player->x = new_x;
    if (!is_wall((int)player->x, (int)(new_y), map))
        player->y = new_y;
}

static void move_player_lr(player_t *player, input_t *input,
    int **map, game_t *game)
{
    float movement_speed = player->speed * game->delta_time * 10;
    float new_x = player->x;
    float new_y = player->y;

    if (input->keys[sfKeyRight] || input->keys[sfKeyD]) {
        new_x += movement_speed * cos(player->angle + (M_PI / 2));
        new_y += movement_speed * sin(player->angle + (M_PI / 2));
    }
    if (input->keys[sfKeyLeft] || input->keys[sfKeyQ]) {
        new_x -= movement_speed * cos(player->angle + (M_PI / 2));
        new_y -= movement_speed * sin(player->angle + (M_PI / 2));
    }
    if (!is_wall((int)(new_x), (int)player->y, map))
        player->x = new_x;
    if (!is_wall((int)player->x, (int)(new_y), map))
        player->y = new_y;
}

static void rotate_player_and_vertical_angle(player_t *player,
    sfRenderWindow *window, game_t *game)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    static sfVector2i last_mouse_position = {0, 0};
    sfVector2i current_mouse_position =
    sfMouse_getPositionRenderWindow(window);
    int delta_x = current_mouse_position.x - last_mouse_position.x;
    float rotation_speed = game->delta_time / 10.0f;

    player->angle += delta_x * rotation_speed;
    if (player->angle < 0)
        player->angle += 2 * M_PI;
    if (player->angle > 2 * M_PI)
        player->angle -= 2 * M_PI;
    sfMouse_setPositionRenderWindow(
        (sfVector2i){window_size.x / 2, window_size.y / 2}, window);
    last_mouse_position = sfMouse_getPositionRenderWindow(window);
}

static void common_key(player_t *player, input_t *input, game_t *game)
{
    if ((input->keys[sfKeyLShift] ||
        sfJoystick_isButtonPressed(0, 9))
        && !player->reloading) {
        player->speed = 2;
        player->stamina -= 100 * game->delta_time;
        if (player->stamina <= 0) {
            player->stamina = 0;
            player->speed = 1;
        }
    } else {
        player->speed = 1;
        player->stamina += 10 * game->delta_time;
        if (player->stamina >= player->maw_stamina)
            player->stamina = player->maw_stamina;
    }
}

static void handle_darkness(input_t *input, player_t *player)
{
    static sfClock* toggle_clock = NULL;
    sfTime elapsed = {0};

    if ((input->keys[sfKeyL] || sfJoystick_isButtonPressed(0, 8))) {
        if (!toggle_clock)
            toggle_clock = sfClock_create();
        elapsed = sfClock_getElapsedTime(toggle_clock);
        if (sfTime_asSeconds(elapsed) > 0.3f) {
            player->darkness_enabled = !player->darkness_enabled;
            sfClock_restart(toggle_clock);
        }
    }
}

void apply_movement(player_t *player, input_t *input,
    game_t *game)
{
    if (game->paused == 1)
        return;
    common_key(player, input, game);
    move_player(player, input, game->map, game);
    rotate_player_and_vertical_angle(player, game->window, game);
    move_player_lr(player, input, game->map, game);
    handle_darkness(input, player);
}
