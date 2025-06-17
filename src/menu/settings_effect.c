/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

void recreate_window(game_t *game, sfVideoMode mode, sfUint32 style)
{
    sfView *view;

    sfRenderWindow_close(game->window);
    sfRenderWindow_destroy(game->window);
    game->window = sfRenderWindow_create(mode, "palwish", style, NULL);
    if (!game->window)
        exit(84);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    view = sfView_create();
    sfView_setSize(view, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
    sfView_setCenter(view, (sfVector2f)
    {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
    sfRenderWindow_setView(game->window, view);
}

void handle_resolution_buttons(game_t *game, float mouse_x,
    float mouse_y, settings_t *s)
{
    sfFloatRect rect_1920;
    sfFloatRect rect_full;

    if (s->btn_1920) {
        rect_1920 = sfSprite_getGlobalBounds(s->btn_1920);
        if (sfFloatRect_contains(&rect_1920, mouse_x, mouse_y)) {
            recreate_window(game, (sfVideoMode){1920, 1080, 32},
    sfResize | sfClose);
        }
    }
    if (s->btn_full) {
        rect_full = sfSprite_getGlobalBounds(s->btn_full);
        if (sfFloatRect_contains(&rect_full, mouse_x, mouse_y)) {
            recreate_window(game, sfVideoMode_getDesktopMode(),
    sfResize | sfClose | sfFullscreen);
        }
    }
}
