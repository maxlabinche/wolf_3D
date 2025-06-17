/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/
#include "palwish.h"

void draw_floor(game_t *game)
{
    sfRectangleShape *floor = sfRectangleShape_create();

    if (!floor)
        return;
    sfRectangleShape_setSize(floor, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
    sfRectangleShape_setPosition(floor, (sfVector2f){0, 0});
    sfRectangleShape_setFillColor(floor, sfColor_fromRGB(100, 100, 100));
    sfRenderWindow_drawRectangleShape(game->window, floor, NULL);
    sfRectangleShape_destroy(floor);
}

void draw_ceiling_part(game_t *game, int pos_x, int tex_offset_x, int width)
{
    int sky_height = (WINDOW_HEIGHT / 2) - 50;
    sfRectangleShape *ceiling = sfRectangleShape_create();

    if (!ceiling)
        return;
    sfRectangleShape_setSize(ceiling, (sfVector2f){width, sky_height});
    sfRectangleShape_setPosition(ceiling, (sfVector2f){pos_x, 0});
    sfRectangleShape_setTexture(ceiling, game->textures->ceiling_texture,
        sfTrue);
    sfRectangleShape_setTextureRect(ceiling,
        (sfIntRect){tex_offset_x, 0, width, sky_height});
    sfRenderWindow_drawRectangleShape(game->window, ceiling, NULL);
    sfRectangleShape_destroy(ceiling);
}

void draw_ceiling(player_t *player, game_t *game)
{
    sfVector2u tex_size =
    sfTexture_getSize(game->textures->ceiling_texture);
    int offset_x = (int)(player->angle * 2.0f *
        (tex_size.x / (2 * M_PI))) % tex_size.x;
    int first_part = tex_size.x - offset_x;

    if (offset_x < 0)
        offset_x += tex_size.x;
    if (first_part > WINDOW_WIDTH)
        first_part = WINDOW_WIDTH;
    draw_ceiling_part(game, 0, offset_x, first_part);
    if (first_part < WINDOW_WIDTH) {
        draw_ceiling_part(game, first_part, 0, WINDOW_WIDTH - first_part);
    }
}

void draw_floor_and_ceiling(player_t *player, game_t *game)
{
    draw_floor(game);
    draw_ceiling(player, game);
}

static sfColor get_darkness(player_t *player,
    float corrected_distance, int side)
{
    sfColor dark_tint = {0, 0, 0, 255};
    float darkness = 0.0f;
    float intensity = 0.0f;

    if (player->darkness_enabled) {
        darkness = corrected_distance / (MAX_DEPTH * 0.3f);
        intensity = 1.0f - (darkness * 1.5f);
        darkness = fminf(0.98f, darkness);
        intensity = fmaxf(0.1f, intensity);
        dark_tint = sfColor_fromRGBA(255 * intensity,
            255 * intensity, 255 * intensity, 255);
        if (side == 0) {
            dark_tint.r *= 0.75f;
            dark_tint.g *= 0.75f;
            dark_tint.b *= 0.75f;
        }
    } else
        dark_tint = sfColor_fromRGBA(255, 255, 255, 255);
    return dark_tint;
}

static wall_render_data_t compute_wall_render_data(game_t *game,
    float ray_angle, raycast_result_t res)
{
    wall_render_data_t data;
    float corrected_distance = res.distance *
    cos(ray_angle - game->player->angle);
    sfVector2u texture_size = sfTexture_getSize(game->textures->wall_texture);

    data.wall_height = (1.0f / corrected_distance) * 1500.0f;
    data.top = (WINDOW_HEIGHT / 2.0f) - (data.wall_height / 2.0f) - 30;
    if (res.side == 0) {
        data.texture_x = fmod(game->player->y + corrected_distance *
        sin(ray_angle), 1.0f) * texture_size.x;
    } else {
        data.texture_x = fmod(game->player->x + corrected_distance *
        cos(ray_angle), 1.0f) * texture_size.x;
    }
    data.darkness = get_darkness(game->player, corrected_distance, res.side);
    return data;
}

static void draw_wall_slice_from_data(game_t *game, int i,
    wall_render_data_t data)
{
    sfRectangleShape *wall_slice = sfRectangleShape_create();
    sfVector2u texture_size;

    if (!wall_slice)
        return;
    texture_size = sfTexture_getSize(game->textures->wall_texture);
    sfRectangleShape_setSize(wall_slice, (sfVector2f){1, data.wall_height});
    sfRectangleShape_setPosition(wall_slice, (sfVector2f){i, data.top});
    sfRectangleShape_setTexture(wall_slice,
        game->textures->wall_texture, sfTrue);
    sfRectangleShape_setTextureRect(wall_slice,
        (sfIntRect){data.texture_x, 0, 1, texture_size.y});
    sfRectangleShape_setFillColor(wall_slice, data.darkness);
    sfRenderWindow_drawRectangleShape(game->window, wall_slice, NULL);
    sfRectangleShape_destroy(wall_slice);
}

void draw_wall_slice(game_t *game, int i,
    float ray_angle, raycast_result_t res)
{
    wall_render_data_t data =
        compute_wall_render_data(game, ray_angle, res);

    draw_wall_slice_from_data(game, i, data);
}
