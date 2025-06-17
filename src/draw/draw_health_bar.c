/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** health_bar
*/

#include "palwish.h"

static void init_health_bar(sfRectangleShape *hp_bar,
    sfRectangleShape *hp_bar_outline)
{
    sfRectangleShape_setFillColor(hp_bar, sfRed);
    sfRectangleShape_setFillColor(hp_bar_outline, sfTransparent);
    sfRectangleShape_setOutlineColor(hp_bar_outline, sfBlack);
    sfRectangleShape_setOutlineThickness(hp_bar_outline, 1);
}

void draw_health_bar(sfRenderWindow *window, object_t object,
    float distance)
{
    float scale = TILE_SIZE / distance;
    sfVector2f obj_pos = sfSprite_getPosition(object.sprite);
    sfRectangleShape *hp_bar = sfRectangleShape_create();
    sfRectangleShape *hp_bar_outline = sfRectangleShape_create();

    sfRectangleShape_setPosition(hp_bar, (sfVector2f){obj_pos.x, obj_pos.y});
    sfRectangleShape_setPosition(hp_bar_outline, (sfVector2f){obj_pos.x,
        obj_pos.y});
    init_health_bar(hp_bar, hp_bar_outline);
    sfRectangleShape_setSize(hp_bar, (sfVector2f){object.health * 10, 10});
    sfRectangleShape_setSize(hp_bar_outline,
        (sfVector2f){object.max_health * 10, 10});
    sfRectangleShape_setScale(hp_bar, (sfVector2f){8 * scale /
        TILE_SIZE * 2.2f, 8 * scale / TILE_SIZE * 2.2f});
    sfRectangleShape_setScale(hp_bar_outline, (sfVector2f){8 * scale /
        TILE_SIZE * 2.2f, 8 * scale / TILE_SIZE * 2.2f});
    sfRenderWindow_drawRectangleShape(window, hp_bar, NULL);
    sfRenderWindow_drawRectangleShape(window, hp_bar_outline, NULL);
    sfRectangleShape_destroy(hp_bar);
    sfRectangleShape_destroy(hp_bar_outline);
}
