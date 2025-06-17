/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

sfTexture *load_arm_1_first(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/gun.png", NULL);
        if (!texture){
            fprintf(stderr, "Failed to load gun texture\n");
            exit(84);
        }
    }
    return texture;
}

sfTexture *load_arm_2_first(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/minigun.png", NULL);
        if (!texture){
            fprintf(stderr, "Failed to load gun texture\n");
            exit(84);
        }
    }
    return texture;
}

sfTexture *load_button_1920(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/bouton/1920_1080.png", NULL);
        if (!texture)
            exit(84);
    }
    return texture;
}

sfTexture *load_button_full(void)
{
    static sfTexture *texture = NULL;

    if (!texture) {
        texture = sfTexture_createFromFile(
            "assets/bouton/full_screen.png", NULL);
        if (!texture)
            exit(84);
    }
    return texture;
}
