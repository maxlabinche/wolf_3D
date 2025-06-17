/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_minimap
*/

#include "palwish.h"

void draw_player_direction_on_minimap(sfRenderWindow *window, player_t *player)
{
    sfVertexArray *line = sfVertexArray_create();
    sfVector2f direction = {cos(player->angle) * 10, sin(player->angle) * 10};

    if (!line)
        exit(84);
    sfVertexArray_setPrimitiveType(line, sfLines);
    sfVertexArray_append(line, (sfVertex){{
        MINIMAP_OFFSET_X + (player->x * MINIMAP_TILE_SIZE),
        MINIMAP_OFFSET_Y + (player->y * MINIMAP_TILE_SIZE)
    }, sfRed, {0, 0}});
    sfVertexArray_append(line, (sfVertex){{
        MINIMAP_OFFSET_X + (player->x * MINIMAP_TILE_SIZE) + direction.x,
        MINIMAP_OFFSET_Y + (player->y * MINIMAP_TILE_SIZE) + direction.y
    }, sfRed, {0, 0}});
    sfRenderWindow_drawVertexArray(window, line, NULL);
    sfVertexArray_destroy(line);
}

void draw_player_on_minimap(sfRenderWindow *window, player_t *player,
    float tile_size)
{
    sfCircleShape *player_dot = sfCircleShape_create();
    float player_dot_size = tile_size * MINIMAP_PLAYER_SIZE / 3;

    if (!player_dot)
        exit(84);
    sfCircleShape_setRadius(player_dot, player_dot_size);
    sfCircleShape_setFillColor(player_dot, sfRed);
    sfCircleShape_setPosition(player_dot, (sfVector2f){
        MINIMAP_OFFSET_X + (player->x * tile_size) - player_dot_size,
        MINIMAP_OFFSET_Y + (player->y * tile_size) - player_dot_size});
    sfRenderWindow_drawCircleShape(window, player_dot, NULL);
    sfCircleShape_destroy(player_dot);
}

void draw_minimap(sfRenderWindow *window, player_t *player, int **map)
{
    sfRectangleShape *tile = sfRectangleShape_create();
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f minimap_size = {window_size.y * 0.2, window_size.y * 0.2};
    float tile_size = minimap_size.x / MAP_WIDTH;

    if (!tile)
        exit(84);
    sfRectangleShape_setSize(tile, (sfVector2f){tile_size, tile_size});
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++) {
            sfRectangleShape_setPosition(tile, (sfVector2f){
                MINIMAP_OFFSET_X + (x * tile_size),
                MINIMAP_OFFSET_Y + (y * tile_size)});
            sfRectangleShape_setFillColor(tile,
                map[y][x] == 1 ? sfWhite : sfBlack);
            sfRectangleShape_setOutlineThickness(tile, 1);
            sfRenderWindow_drawRectangleShape(window, tile, NULL);
        }
    draw_player_on_minimap(window, player, tile_size);
    sfRectangleShape_destroy(tile);
}
