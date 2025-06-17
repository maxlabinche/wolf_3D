/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

void handle_window_resize(sfSprite *bg_sprite,
    sfSprite *start_button, sfSprite *quit_button)
{
    sfVector2u bg_size = sfTexture_getSize(sfSprite_getTexture(bg_sprite));
    sfVector2f bg_scale = {(float)1920 / bg_size.x,
        (float)1080 / bg_size.y};

    sfSprite_setScale(bg_sprite, bg_scale);
    setup_menu_buttons(&start_button, &quit_button);
}

int handle_mouse_click(game_t *game, sfSprite *start_button,
    sfSprite *quit_button, int *code)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(
        game->window, pixel_pos, NULL);
    sfFloatRect start_bounds = sfSprite_getGlobalBounds(start_button);
    sfFloatRect quit_bounds = sfSprite_getGlobalBounds(quit_button);

    *code = 1;
    if (sfFloatRect_contains(&start_bounds, world_pos.x, world_pos.y)) {
        return 1;
    }
    if (sfFloatRect_contains(&quit_bounds, world_pos.x, world_pos.y)) {
        sfRenderWindow_close(game->window);
        return 1;
    }
    return 0;
}

static int handle_credits_click(game_t *game,
    sfSprite *credits_page, sfSprite *bg, int *code)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(
        game->window, pixel_pos, NULL);
    sfFloatRect credits_bounds = sfSprite_getGlobalBounds(credits_page);

    *code = 0;
    if (sfFloatRect_contains(&credits_bounds, world_pos.x, world_pos.y)) {
        sfRenderWindow_clear(game->window, sfBlack);
        set_credits_page(game, bg);
        return 1;
    }
    return 0;
}

static int handle_settings_click(game_t *game,
    sfSprite *settings_button, sfSprite *bg, int *code)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(
        game->window, pixel_pos, NULL);
    sfFloatRect settings_bounds = sfSprite_getGlobalBounds(settings_button);

    *code = 0;
    if (sfFloatRect_contains(&settings_bounds, world_pos.x, world_pos.y)) {
        setting_loop(game, bg);
        return 1;
    }
    return 0;
}

int handle_menu_events(game_t *game, sfSprite **all_sprites)
{
    sfEvent event;
    int code = 0;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(game->window);
        if (event.type == sfEvtResized) {
            handle_window_resize(all_sprites[0],
                all_sprites[1], all_sprites[2]);
        }
        if (event.type == sfEvtMouseButtonPressed &&
            event.mouseButton.button == sfMouseLeft &&
            (handle_mouse_click(game, all_sprites[1], all_sprites[2], &code) ||
            handle_credits_click(game,
                all_sprites[3], all_sprites[0], &code) ||
            handle_settings_click(game,
                all_sprites[4], all_sprites[0], &code)))
            return code;
    }
    return 0;
}

void render_menu(game_t *game,
    sfSprite **all_sprites)
{
    sfRenderWindow_clear(game->window, sfBlack);
    sfRenderWindow_drawSprite(game->window, all_sprites[0], NULL);
    sfRenderWindow_drawSprite(game->window, all_sprites[1], NULL);
    sfRenderWindow_drawSprite(game->window, all_sprites[2], NULL);
    sfRenderWindow_drawSprite(game->window, all_sprites[3], NULL);
    sfRenderWindow_drawSprite(game->window, all_sprites[4], NULL);
    sfRenderWindow_display(game->window);
}

static sfSprite **setup_menu(void)
{
    sfSprite **all_sprites = malloc(sizeof(sfSprite *) * 5);

    if (!all_sprites)
        exit(84);
    all_sprites[0] = load_bg();
    all_sprites[1] = NULL;
    all_sprites[2] = NULL;
    all_sprites[3] = NULL;
    all_sprites[4] = NULL;
    setup_menu_buttons(&all_sprites[1], &all_sprites[2]);
    setup_menu_buttons_2(&all_sprites[3], &all_sprites[4]);
    return all_sprites;
}

void menu_loop(game_t *game)
{
    sfSprite **all_sprites = setup_menu();

    if (game->game_music)
        sfMusic_stop(game->game_music);
    if (game->menu_music)
        sfMusic_play(game->menu_music);
    while (sfRenderWindow_isOpen(game->window)) {
        if (handle_menu_events(game, all_sprites)) {
            break;
        }
        render_menu(game, all_sprites);
    }
    free(all_sprites);
}
