/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

void draw_settings_background(game_t *game, sfSprite *bg, settings_t *s)
{
    if (bg)
        sfRenderWindow_drawSprite(game->window, bg, NULL);
    if (s->btn_1920)
        sfRenderWindow_drawSprite(game->window, s->btn_1920, NULL);
    if (s->btn_full)
        sfRenderWindow_drawSprite(game->window, s->btn_full, NULL);
}

void init_slider1_settings(settings_t *s)
{
    s->bar_x = 100;
    s->bar_y = 1000;
    s->bar_w = 300;
    s->bar_h = 50;
    s->cursor_w = 20;
    s->cursor_h = 70;
}

void init_slider2_settings(settings_t *s)
{
    s->bar2_x = 1520;
    s->bar2_y = 1000;
    s->bar2_w = 300;
    s->bar2_h = 50;
    s->cursor2_w = 20;
    s->cursor2_h = 70;
}

static void draw_slider1(game_t *game, settings_t *s)
{
    sfRectangleShape *cursor;
    sfRectangleShape *bar = sfRectangleShape_create();

    sfRectangleShape_setPosition(bar, (sfVector2f){s->bar_x, s->bar_y});
    sfRectangleShape_setSize(bar, (sfVector2f){s->bar_w, s->bar_h});
    sfRectangleShape_setFillColor(bar, sfBlack);
    sfRenderWindow_drawRectangleShape(game->window, bar, NULL);
    cursor = sfRectangleShape_create();
    sfRectangleShape_setPosition(cursor, (sfVector2f){
        s->cursor_x, s->bar_y - (s->cursor_h - s->bar_h) / 2});
    sfRectangleShape_setSize(cursor, (sfVector2f){s->cursor_w, s->cursor_h});
    sfRectangleShape_setFillColor(cursor, sfColor_fromRGB(255, 140, 0));
    sfRenderWindow_drawRectangleShape(game->window, cursor, NULL);
    sfRectangleShape_destroy(bar);
    sfRectangleShape_destroy(cursor);
}

static void draw_slider2(game_t *game, settings_t *s)
{
    sfRectangleShape *cursor;
    sfRectangleShape *bar = sfRectangleShape_create();

    sfRectangleShape_setPosition(bar, (sfVector2f){s->bar2_x, s->bar2_y});
    sfRectangleShape_setSize(bar, (sfVector2f){s->bar2_w, s->bar2_h});
    sfRectangleShape_setFillColor(bar, sfBlack);
    sfRenderWindow_drawRectangleShape(game->window, bar, NULL);
    cursor = sfRectangleShape_create();
    sfRectangleShape_setPosition(cursor, (sfVector2f){
        s->cursor2_x, s->bar2_y - (s->cursor2_h - s->bar2_h) / 2});
    sfRectangleShape_setSize(cursor, (sfVector2f){s->cursor2_w, s->cursor2_h});
    sfRectangleShape_setFillColor(cursor, sfColor_fromRGB(0, 200, 255));
    sfRenderWindow_drawRectangleShape(game->window, cursor, NULL);
    sfRectangleShape_destroy(bar);
    sfRectangleShape_destroy(cursor);
}

void draw_slider_label(sfRenderWindow *window, sfFont *font,
    const char *text, sfVector2f position)
{
    sfText *label = sfText_create();

    if (!label)
        return;
    sfText_setFont(label, font);
    sfText_setString(label, text);
    sfText_setCharacterSize(label, 36);
    sfText_setColor(label, sfWhite);
    sfText_setPosition(label, position);
    sfRenderWindow_drawText(window, label, NULL);
    sfText_destroy(label);
}

void draw_settings_ui(game_t *game, sfSprite *bg, settings_t *s)
{
    sfFont *font = load_font();

    if (!font)
        return;
    sfRenderWindow_clear(game->window, sfBlack);
    draw_settings_background(game, bg, s);
    draw_slider1(game, s);
    draw_slider2(game, s);
    draw_slider_label(game->window, font, "Musique menu",
        (sfVector2f){s->bar_x, s->bar_y - 60});
    draw_slider_label(game->window, font, "Musique jeu",
        (sfVector2f){s->bar2_x, s->bar2_y - 60});
    sfRenderWindow_display(game->window);
}
