/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** shoot
*/

#include "palwish.h"

void change_weapon(player_t *player, input_t *input)
{
    if (input->keys[sfKeyNum1]
        && player->actual_weapon != 0) {
        player->actual_weapon = 0;
        sfClock_restart(player->shoot_clock);
    }
    if ((input->keys[sfKeyNum2]
        || sfMouse_isButtonPressed(sfMouseMiddle))
        && player->actual_weapon != 1) {
        player->actual_weapon = 1;
        sfClock_restart(player->shoot_clock);
    }
}

void reload_weapon(player_t *player, input_t *input)
{
    sfTime elapsed;

    if (input->keys[sfKeyR] && !player->reloading) {
        player->reloading = true;
        sfClock_restart(player->reload_clock);
    }
    if (player->weapon[player->actual_weapon].munitions
        >= player->weapon[player->actual_weapon].max_munitions
        || !player->reloading)
        return;
    elapsed = sfClock_getElapsedTime(player->reload_clock);
    if (sfTime_asSeconds(elapsed) >
        player->weapon[player->actual_weapon].reload_time){
        sfClock_restart(player->reload_clock);
        player->reloading = false;
        player->weapon[player->actual_weapon].munitions =
            player->weapon[player->actual_weapon].max_munitions;
    }
}

void shoot(game_t *game, player_t *player)
{
    sfFloatRect bounds;
    sfVector2f cursor_pos = sfCircleShape_getPosition(player->cursor);
    float distance = 0;

    player->weapon[player->actual_weapon].munitions--;
    for (int i = 0; i < game->object_count; i++) {
        bounds = sfSprite_getGlobalBounds(game->objects[i].sprite);
        if (game->objects[i].is_visible &&
        sfFloatRect_contains(&bounds, cursor_pos.x, cursor_pos.y) &&
        is_object_visible(player, game->objects[i], game->map, &distance)) {
            game->objects[i].health
            -= player->weapon[player->actual_weapon].damage;
            spawn_object_hit_particles(game);
            game->objects[i].has_changed = true;
        }
        if (game->objects[i].health <= 0){
            game->objects[i].health = 0;
            game->objects[i].is_visible = false;
        }
    }
}

void handle_shooting_clock(player_t *player, game_t *game, input_t *input)
{
    sfTime time;

    if (game->paused)
        return;
    time = sfClock_getElapsedTime(player->shoot_clock);
    if (sfTime_asSeconds(time)
        > player->weapon[player->actual_weapon].fire_rate
        && (sfMouse_isButtonPressed(sfMouseLeft)
        || input->keys[sfKeySpace])) {
        player->weapon[player->actual_weapon].etat = 1;
        sfMusic_play(player->weapon[player->actual_weapon].music);
        shoot(game, player);
        sfClock_restart(player->shoot_clock);
    }
}

void handle_shooting(player_t *player, game_t *game, input_t *input)
{
    if (game->paused)
        return;
    reload_weapon(player, input);
    if (player->reloading)
        return;
    change_weapon(player, input);
    if (player->weapon[player->actual_weapon].munitions <= 0) {
        return;
    }
    handle_shooting_clock(player, game, input);
    if (game->offline == true)
        remove_dead_objects(game);
}
