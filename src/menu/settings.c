/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

static sfSprite *create_settings_sprite_1920_1080(void)
{
    sfTexture *texture = load_button_1920();
    sfSprite *sprite = sfSprite_create();

    if (!texture)
        return NULL;
    if (!sprite) {
        sfTexture_destroy(texture);
        return NULL;
    }
    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}

static sfSprite *create_settings_sprite_full_screen(void)
{
    sfTexture *texture = load_button_full();
    sfSprite *sprite = sfSprite_create();

    if (!texture)
        return NULL;
    if (!sprite) {
        sfTexture_destroy(texture);
        return NULL;
    }
    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}

void init_settings_sliders(settings_t *settings, game_t *game)
{
    init_slider1_settings(settings);
    settings->min_x = settings->bar_x;
    settings->max_x = settings->bar_x +
    settings->bar_w - settings->cursor_w;
    settings->volume = game->menu_music ?
    sfMusic_getVolume(game->menu_music) : 100.0f;
    settings->cursor_x = settings->min_x +
    (settings->max_x - settings->min_x) * (settings->volume / 100.0f);
    settings->dragging = 0;
    init_slider2_settings(settings);
    settings->min2_x = settings->bar2_x;
    settings->max2_x = settings->bar2_x +
    settings->bar2_w - settings->cursor2_w;
    settings->volume2 = game->game_music ?
    sfMusic_getVolume(game->game_music) : 100.0f;
    settings->cursor2_x = settings->min2_x +
    (settings->max2_x - settings->min2_x) * (settings->volume2 / 100.0f);
    settings->dragging2 = 0;
}

static void init_settings_buttons(settings_t *settings)
{
    settings->btn_1920 = create_settings_sprite_1920_1080();
    settings->btn_full = create_settings_sprite_full_screen();
    if (settings->btn_1920) {
        sfSprite_setScale(settings->btn_1920, (sfVector2f){1.0f, 1.0f});
        sfSprite_setPosition(settings->btn_1920, (sfVector2f){655, 25});
    }
    if (settings->btn_full) {
        sfSprite_setScale(settings->btn_full, (sfVector2f){1.0f, 1.0f});
        sfSprite_setPosition(settings->btn_full, (sfVector2f){655, 400});
    }
}

void handle_click(game_t *game, float mouse_x, float mouse_y, settings_t *s)
{
    handle_resolution_buttons(game, mouse_x, mouse_y, s);
}

void handle_slider_interaction(settings_t *s, game_t *game)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f mouse =
        sfRenderWindow_mapPixelToCoords(game->window, pixel_pos, NULL);
    float mouse_x = mouse.x;
    float mouse_y = mouse.y;
    float cursor1_y = s->bar_y - (s->cursor_h - s->bar_h) / 2;
    float cursor2_y = s->bar2_y - (s->cursor2_h - s->bar2_h) / 2;

    if (mouse_x >= s->cursor_x && mouse_x <= s->cursor_x + s->cursor_w &&
        mouse_y >= cursor1_y && mouse_y <= cursor1_y + s->cursor_h)
        s->dragging = 1;
    if (mouse_x >= s->cursor2_x && mouse_x <= s->cursor2_x + s->cursor2_w &&
        mouse_y >= cursor2_y && mouse_y <= cursor2_y + s->cursor2_h)
        s->dragging2 = 1;
}

static void update_slider_position(settings_t *s, game_t *game)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f mouse =
        sfRenderWindow_mapPixelToCoords(game->window, pixel_pos, NULL);
    float mouse_x = mouse.x;

    if (s->dragging) {
        s->cursor_x = mouse_x - s->cursor_w / 2;
        if (s->cursor_x < s->min_x)
            s->cursor_x = s->min_x;
        if (s->cursor_x > s->max_x)
            s->cursor_x = s->max_x;
    }
    if (s->dragging2) {
        s->cursor2_x = mouse_x - s->cursor2_w / 2;
        if (s->cursor2_x < s->min2_x)
            s->cursor2_x = s->min2_x;
        if (s->cursor2_x > s->max2_x)
            s->cursor2_x = s->max2_x;
    }
}

static void handle_settings_events(game_t *game, settings_t *s, int *running)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(game->window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            *running = 0;
        if (event.type == sfEvtMouseButtonPressed &&
            event.mouseButton.button == sfMouseLeft) {
            handle_click(game, event.mouseButton.x, event.mouseButton.y, s);
            handle_slider_interaction(s, game);
        }
        if (event.type == sfEvtMouseButtonReleased &&
            event.mouseButton.button == sfMouseLeft) {
            s->dragging = 0;
            s->dragging2 = 0;
        }
        if (event.type == sfEvtMouseMoved)
            update_slider_position(s, game);
    }
}

void setting_loop(game_t *game, sfSprite *bg)
{
    settings_t s;
    int running = 1;

    init_settings_sliders(&s, game);
    init_settings_buttons(&s);
    while (sfRenderWindow_isOpen(game->window) && running) {
        handle_settings_events(game, &s, &running);
        s.volume = ((s.cursor_x - s.min_x) / (s.max_x - s.min_x)) * 100.0f;
        s.volume2 = ((s.cursor2_x - s.min2_x) /
        (s.max2_x - s.min2_x)) * 100.0f;
        if (game->menu_music)
            sfMusic_setVolume(game->menu_music, s.volume);
        if (game->game_music)
            sfMusic_setVolume(game->game_music, s.volume2);
        draw_settings_ui(game, bg, &s);
    }
    if (s.btn_1920)
        sfSprite_destroy(s.btn_1920);
    if (s.btn_full)
        sfSprite_destroy(s.btn_full);
}
