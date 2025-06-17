/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_minimap
*/

#include "palwish.h"

void show_latency(game_t *game, sfText *text)
{
    size_t buffer_size = 13 + float_size(game->latency);
    char *buffer = malloc(buffer_size * sizeof(char));

    if (!buffer)
        return;
    if (!text || game->offline == true) {
        free(buffer);
        return;
    }
    snprintf(buffer, buffer_size, "Latency: %.2f ms", game->latency);
    sfText_setString(text, buffer);
    sfText_setPosition(text, (sfVector2f){
        WINDOW_WIDTH - 270, 15});
    sfRenderWindow_drawText(game->window, text, NULL);
    free(buffer);
}

void show_sor(game_t *game, sfText *text)
{
    size_t buffer_size = 7 + int_size(game->send_object);
    char *buffer = malloc(buffer_size * sizeof(char));

    if (!buffer)
        return;
    if (!text || game->offline == true) {
        free(buffer);
        return;
    }
    snprintf(buffer, buffer_size, "SO/R: %d", game->send_object);
    sfText_setString(text, buffer);
    sfText_setPosition(text, (sfVector2f){
        WINDOW_WIDTH - 270, 85});
    sfRenderWindow_drawText(game->window, text, NULL);
    free(buffer);
}

void show_ror(game_t *game, sfText *text)
{
    size_t buffer_size = 7 + int_size(game->receive_object);
    char *buffer = malloc(buffer_size * sizeof(char));

    if (!buffer)
        return;
    if (!text || game->offline == true) {
        free(buffer);
        return;
    }
    snprintf(buffer, buffer_size, "RO/R: %d", game->receive_object);
    sfText_setString(text, buffer);
    sfText_setPosition(text, (sfVector2f){
        WINDOW_WIDTH - 270, 120});
    sfRenderWindow_drawText(game->window, text, NULL);
    free(buffer);
}

void total_objects(game_t *game, sfText *text)
{
    size_t buffer_size = 10 + int_size(game->object_count);
    char *buffer = malloc(buffer_size * sizeof(char));

    if (!buffer)
        return;
    if (!text || game->offline == true) {
        free(buffer);
        return;
    }
    snprintf(buffer, buffer_size, "Objects: %d", game->object_count);
    sfText_setString(text, buffer);
    sfText_setPosition(text, (sfVector2f){
        WINDOW_WIDTH - 270, 50});
    sfRenderWindow_drawText(game->window, text, NULL);
    free(buffer);
}

void show_statistics(game_t *game)
{
    sfText *text = sfText_create();
    sfFont *font = load_font();

    if (!text || !font || game->offline == true)
        return;
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 30);
    show_latency(game, text);
    total_objects(game, text);
    show_sor(game, text);
    show_ror(game, text);
    sfText_destroy(text);
}
