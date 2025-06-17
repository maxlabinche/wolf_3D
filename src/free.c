/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** free
*/

#include "palwish.h"

void free_game(game_t *game)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        free(game->map[y]);
    free(game->map);
    if (game->particles) {
        free(game->particles->particles);
        free(game->particles);
    }
    sfTexture_destroy(game->textures->wall_texture);
    sfTexture_destroy(game->textures->ceiling_texture);
    free(game->textures);
    for (int i = 0; i < game->object_count; i++)
        if (game->objects[i].sprite)
            sfSprite_destroy(game->objects[i].sprite);
    free(game->objects);
}

void free_static_resources(void)
{
    sfTexture_destroy(load_player());
    sfTexture_destroy(load_enemi());
    sfTexture_destroy(load_arm_1_first());
    sfTexture_destroy(load_arm_2_first());
    sfSprite_destroy(load_bg());
    sfSprite_destroy(load_settings());
    sfFont_destroy(load_font());
}

static void destroy_game_music(game_t *game)
{
    if (game->menu_music)
        sfMusic_destroy(game->menu_music);
    if (game->game_music)
        sfMusic_destroy(game->game_music);
}

int destroy_game(game_t *game)
{
    if (game->offline == true) {
        backup_objects(game);
    }
    destroy_game_music(game);
    sfRenderWindow_destroy(game->window);
    sfClock_destroy(game->clock);
    free_game(game);
    free_static_resources();
    return 0;
}
