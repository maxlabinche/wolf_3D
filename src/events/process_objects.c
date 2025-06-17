/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_minimap
*/

#include "palwish.h"

int get_index_object_by_user(game_t *game, int user)
{
    for (int i = 0; i < game->object_count; i++) {
        if (game->objects[i].user == user)
            return (i);
    }
    return (-1);
}

float calculate_depth(float distance, float angle)
{
    float depth = distance * cos(angle);

    if (depth < 0.1)
        return 0.1;
    return depth;
}

float calculate_distance(float dx, float dy)
{
    float distance = sqrt(dx * dx + dy * dy);

    return (distance < 0.1) ? 0.1 : distance;
}

float calculate_relative_angle(float angle_to_object,
    float player_angle)
{
    float relative_angle = angle_to_object - player_angle;

    if (relative_angle < -(M_PI))
        relative_angle += 2 * M_PI;
    if (relative_angle > M_PI)
        relative_angle -= 2 * M_PI;
    return relative_angle;
}
