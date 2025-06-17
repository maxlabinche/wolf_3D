/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"

static float get_angle_to_player(player_t *player,
    object_t *obj, float *dx, float *dy)
{
    *dx = player->x - obj->x;
    *dy = player->y - obj->y;
    return atan2f(*dy, *dx);
}

static void rotate_enemy_towards_player(object_t *obj, float angle_to_pl)
{
    float turn_speed = 0.05f;
    float delta = calculate_relative_angle(angle_to_pl, obj->angle);

    if (fabsf(delta) > turn_speed)
        obj->angle += (delta > 0 ? turn_speed : -turn_speed);
    else
        obj->angle = angle_to_pl;
    if (obj->angle < - M_PI)
        obj->angle += 2 * M_PI;
    if (obj->angle > M_PI)
        obj->angle -= 2 * M_PI;
}

static bool try_enemy_shoot(game_t *game, player_t *player,
    object_t *obj, float angle_to_pl)
{
    float rel_en_ang;
    float distance;

    if (!obj)
        return false;
    if (isnan(obj->angle) || obj->angle < - M_PI || obj->angle > M_PI)
        obj->angle = 0.0f;
    rel_en_ang = calculate_relative_angle(angle_to_pl, obj->angle);
    if (fabsf(rel_en_ang) < (FOV / 2)
        && is_object_visible(player, *obj, game->map, &distance)) {
        if ((rand() % 100) < 5) {
            player->health -= 0.07f;
        }
        return true;
    }
    return false;
}

static void pursue_player(game_t *game, player_t *player, object_t *obj)
{
    const float STEP = 0.05f;
    float dx = player->x - obj->x;
    float dy = player->y - obj->y;
    float distance = calculate_distance(dx, dy);
    float angle = atan2f(dy, dx);
    float nx = obj->x + cosf(angle) * STEP;
    float ny = obj->y + sinf(angle) * STEP;

    if (distance <= 3.0f)
        return;
    if (!is_wall((int)nx, (int)obj->y, game->map))
        obj->x = nx;
    if (!is_wall((int)obj->x, (int)ny, game->map))
        obj->y = ny;
}

static void update_enemy_ai(game_t *game, player_t *player, object_t *obj)
{
    float dx;
    float dy;
    float angle_to_pl;

    if (obj->type != 1 || !obj->is_visible || obj->health <= 0)
        return;
    angle_to_pl = get_angle_to_player(player, obj, &dx, &dy);
    calculate_distance(dx, dy);
    rotate_enemy_towards_player(obj, angle_to_pl);
    try_enemy_shoot(game, player, obj, angle_to_pl);
    pursue_player(game, player, obj);
}

void move_objects_randomly(game_t *game, player_t *player)
{
    for (int i = 0; i < game->object_count; i++) {
        update_enemy_ai(game, player, &game->objects[i]);
    }
}
