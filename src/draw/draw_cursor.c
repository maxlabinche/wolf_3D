/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_cursor
*/

#include "palwish.h"

void draw_cursor(sfRenderWindow *window, player_t *player)
{
    sfVector2f cursor_pos = {
        WINDOW_WIDTH / 2,
        WINDOW_HEIGHT / 2
    };

    if (!player->cursor)
        return;
    sfCircleShape_setRadius(player->cursor, 5);
    sfCircleShape_setFillColor(player->cursor, sfRed);
    sfCircleShape_setOutlineColor(player->cursor, sfBlack);
    sfCircleShape_setOutlineThickness(player->cursor, 2);
    sfCircleShape_setPosition(player->cursor, cursor_pos);
    sfRenderWindow_drawCircleShape(window, player->cursor, NULL);
}
