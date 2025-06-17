/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

sfTexture *load_player(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/player.png", NULL);
        if (!texture) {
            fprintf(stderr, "Failed to load player texture\n");
            exit(84);
        }
    }
    return texture;
}

sfTexture *load_enemi(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/enemi.png", NULL);
        if (!texture) {
            fprintf(stderr, "Failed to load enemi texture\n");
            exit(84);
        }
    }
    return texture;
}

sfMusic *load_pan_1(void)
{
    static sfMusic *music = NULL;

    if (!music) {
        music = sfMusic_createFromFile(
            "assets/musics/pan_silents.mp3");
        if (!music) {
            fprintf(stderr, "Failed to load pan music\n");
            exit(84);
        }
    }
    return music;
}
