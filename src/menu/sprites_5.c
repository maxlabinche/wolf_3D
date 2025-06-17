/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

void load_music_menu(game_t *game)
{
    game->menu_music = sfMusic_createFromFile("assets/musics/menu.ogg");
    game->game_music = sfMusic_createFromFile("assets/musics/game.ogg");
    if (!game->menu_music || !game->game_music) {
        exit(84);
    }
}
