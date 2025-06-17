/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

void set_button_position(sfSprite *button, float x, float y)
{
    sfVector2f position = {x, y};

    sfSprite_setPosition(button, position);
}

void setup_menu_buttons(sfSprite **start_button,
    sfSprite **quit_button)
{
    *start_button = load_start();
    *quit_button = load_quit();
    sfSprite_setScale(*start_button, (sfVector2f){0.2f, 0.2f});
    sfSprite_setScale(*quit_button, (sfVector2f){0.15f, 0.15f});
    set_button_position(*start_button,
        (1920 -
            sfSprite_getGlobalBounds(*start_button).width) / 2.0f - 100,
        (1080 -
            sfSprite_getGlobalBounds(*start_button).height)
        / 2.0f);
    set_button_position(*quit_button,
        1920 -
        sfSprite_getGlobalBounds(*quit_button).width - 20,
        1080 -
        sfSprite_getGlobalBounds(*quit_button).height - 20);
}

void setup_menu_buttons_2(sfSprite **credits,
    sfSprite **settings)
{
    *credits = load_credits();
    sfSprite_setScale(*credits, (sfVector2f){0.35f, 0.35f});
    set_button_position(*credits,
        (1920 -
            sfSprite_getGlobalBounds(*credits).width) / 2.0f - 400,
        (1080 -
            sfSprite_getGlobalBounds(*credits).height)
        / 2.0f + 220);
    *settings = load_settings();
    sfSprite_setScale(*settings, (sfVector2f){0.35f, 0.35f});
    set_button_position(*settings,
        (1920 -
            sfSprite_getGlobalBounds(*settings).width) / 2.0f + 350,
        (1080 -
            sfSprite_getGlobalBounds(*settings).height)
        / 2.0f + 350);
}
