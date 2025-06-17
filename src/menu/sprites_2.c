/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

sfSprite *load_settings(void)
{
    static sfSprite *sprite = NULL;

    if (!sprite) {
        sprite = load_sprite(
            "assets/bouton/settings.png",
            "Failed to load settings button texture"
        );
    }
    return sprite;
}

sfFont *load_font(void)
{
    static sfFont *font = NULL;

    if (!font) {
        font = sfFont_createFromFile(
            "assets/fonts/Monocraft.ttf");
        if (!font) {
            fprintf(stderr, "Failed to load font\n");
            exit(84);
        }
    }
    return font;
}

sfSoundBuffer *load_key_buffer_buffer(void)
{
    static sfSoundBuffer *buffer = NULL;

    if (!buffer) {
        buffer = sfSoundBuffer_createFromFile(
            "assets/musics/key.mp3");
        if (!buffer) {
            fprintf(stderr, "Failed to load key buffer sound\n");
            exit(84);
        }
    }
    return buffer;
}

sfTexture *load_wall(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/textures/wall.png", NULL);
        if (!texture) {
            fprintf(stderr, "Failed to load wall texture\n");
            exit(84);
        }
    }
    return texture;
}

sfTexture *load_ceiling(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/textures/sky.png", NULL);
        if (!texture) {
            fprintf(stderr, "Failed to load ceiling texture\n");
            exit(84);
        }
    }
    return texture;
}
