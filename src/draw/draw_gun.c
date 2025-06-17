/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_gun
*/

#include "palwish.h"

static void draw_and_destroy_sprite(sfRenderWindow *window,
    sfSprite *sprite, sfVector2f position)
{
    sfSprite_setPosition(sprite, position);
    sfSprite_setScale(sprite, (sfVector2f){2, 2});
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_destroy(sprite);
}

static void setup_gun_sprite(sfSprite *sprite, player_t *player,
    int current_frame)
{
    sfSprite_setTexture(sprite,
        player->weapon[player->actual_weapon].texture, sfFalse);
    if (player->weapon[player->actual_weapon].etat == 1)
        sfSprite_setTextureRect(sprite, (sfIntRect){
            612 * current_frame, 0, 612, 408});
    if (current_frame == 0)
        player->weapon[player->actual_weapon].etat = 0;
}

void draw_gun(sfRenderWindow *window, player_t *player, game_t *game)
{
    static float offset = 0;
    static int direction = 1;
    static float animation_timer = 0;
    static int current_frame = 0;
    sfSprite *sprite = sfSprite_create();
    sfVector2f sprite_position = { 1920 / (1080 / 2.0f) + 850,
        1920 / (1080 / 2.0f) + offset + 350};

    if (!sprite)
        return;
    offset += direction * game->delta_time * 50.0f;
    if (offset > 10 || offset < -10)
        direction = -direction;
    animation_timer += game->delta_time;
    if (animation_timer >= 0.01f) {
        current_frame = (current_frame + 1) % 8;
        animation_timer = 0;
    }
    setup_gun_sprite(sprite, player, current_frame);
    draw_and_destroy_sprite(window, sprite, sprite_position);
}
