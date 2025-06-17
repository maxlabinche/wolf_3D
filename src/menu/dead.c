/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

static void draw_dead_text(game_t *game,
    sfText *text, sfFont *font, sfVector2f text_pos)
{
    sfText_setString(text, "You are dead");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 100);
    sfText_setPosition(text, text_pos);
    sfText_setColor(text, sfRed);
    sfRenderWindow_drawText(game->window, text, NULL);
}

static void draw_restart_button(game_t *game,
    sfText *text, sfVector2f button_pos)
{
    sfRectangleShape *button = sfRectangleShape_create();

    sfRectangleShape_setSize(button, (sfVector2f){180, 50});
    sfRectangleShape_setPosition(button, button_pos);
    sfRectangleShape_setFillColor(button, sfColor_fromRGB(200, 0, 0));
    sfRenderWindow_drawRectangleShape(game->window, button, NULL);
    sfText_setString(text, "Restart");
    sfText_setCharacterSize(text, 30);
    sfText_setColor(text, sfWhite);
    sfText_setPosition(text, (sfVector2f){button_pos.x + 25,
        button_pos.y + 8});
    sfRenderWindow_drawText(game->window, text, NULL);
    sfRectangleShape_destroy(button);
}

static void handle_restart_click(game_t *game,
    player_t *player, sfVector2f button_pos)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(
        game->window, pixel_pos, NULL);
    sfFloatRect button_bounds = {button_pos.x, button_pos.y, 180, 50};
    sfVector2u window_size = sfRenderWindow_getSize(game->window);

    if (sfMouse_isButtonPressed(sfMouseLeft) &&
        sfFloatRect_contains(&button_bounds, world_pos.x, world_pos.y)) {
        game->paused = 0;
        game->whoami = (rand() + time(NULL)) % 991 + 10;
        sfMouse_setPositionRenderWindow(
            (sfVector2i){window_size.x / 2, window_size.y / 2}, game->window);
        sfRenderWindow_setMouseCursorGrabbed(game->window, sfTrue);
        sfRenderWindow_setMouseCursorVisible(game->window, sfFalse);
        init_player(player, game->map);
    }
}

void draw_dead_menu(game_t *game, player_t *player)
{
    sfVector2u window_size = sfRenderWindow_getSize(game->window);
    sfVector2f text_pos = {window_size.x / (window_size.y / 2.0f) + 600,
        window_size.y / (window_size.y / 2.0f) + 0 + 400};
    sfVector2f button_pos = {window_size.x / (window_size.y / 2.0f) + 880,
        window_size.y / (window_size.y / 2.0f) + 0 + 550};
    sfText *text = sfText_create();
    sfFont *font = load_font();

    game->paused = 1;
    sfRenderWindow_setMouseCursorGrabbed(game->window, sfFalse);
    sfRenderWindow_setMouseCursorVisible(game->window, sfTrue);
    draw_dead_text(game, text, font, text_pos);
    draw_restart_button(game, text, button_pos);
    handle_restart_click(game, player, button_pos);
    sfText_destroy(text);
}
