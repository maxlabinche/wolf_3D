/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_minimap
*/

#include "palwish.h"

void delete_object(game_t *game, int index)
{
    if (index < 0 || index >= game->object_count)
        return;
    if (game->objects[index].sprite)
        sfSprite_destroy(game->objects[index].sprite);
    for (int i = index; i < game->object_count - 1; i++) {
        game->objects[i] = game->objects[i + 1];
    }
    game->object_count--;
    game->objects = realloc(game->objects,
        sizeof(object_t) * game->object_count);
    if (game->object_count > 0 && !game->objects)
        exit(84);
}

void remove_dead_objects(game_t *game)
{
    for (int i = 0; i < game->object_count; i++) {
        if (game->objects[i].health <= 0) {
            delete_object(game, i);
            i--;
        }
    }
}
