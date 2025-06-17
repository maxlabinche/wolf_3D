/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

sfSprite *load_sprite(const char *filename, const char *error_message)
{
    sfTexture *texture;
    sfSprite *sprite;

    texture = sfTexture_createFromFile(filename, NULL);
    sprite = sfSprite_create();
    if (!texture || !sprite) {
        fprintf(stderr, "%s\n", error_message);
        return NULL;
    }
    sfSprite_setTexture(sprite, texture, sfTrue);
    return sprite;
}

sfSprite *load_bg(void)
{
    static sfSprite *sprite = NULL;

    if (!sprite) {
        sprite = load_sprite(
            "assets/bouton/background.png",
            "Failed to load background texture"
        );
    }
    if (!sprite) {
        exit(84);
    }
    return sprite;
}

sfSprite *load_start(void)
{
    static sfSprite *sprite = NULL;

    if (!sprite) {
        sprite = load_sprite(
            "assets/bouton/start.png",
            "Failed to load start button texture"
        );
    }
    if (!sprite) {
        exit(84);
    }
    return sprite;
}

sfSprite *load_quit(void)
{
    static sfSprite *sprite = NULL;

    if (!sprite) {
        sprite = load_sprite(
            "assets/bouton/exit.png",
            "Failed to load quit button texture"
        );
    }
    if (!sprite) {
        exit(84);
    }
    return sprite;
}

sfSprite *load_credits(void)
{
    static sfSprite *sprite = NULL;

    if (!sprite) {
        sprite = load_sprite(
            "assets/bouton/credits.png",
            "Failed to load credits button texture"
        );
    }
    if (!sprite) {
        exit(84);
    }
    return sprite;
}
