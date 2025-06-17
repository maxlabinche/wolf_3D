/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_hud
*/

#include "palwish.h"

void draw_hud(sfRenderWindow *window, player_t *player)
{
    draw_hud_health_bar(window, player);
    draw_stamina_bar(window, player);
    draw_amunitions(window, player);
}

static void draw_ammo_background(sfRenderWindow *window, sfVector2f position)
{
    sfConvexShape *shape = sfConvexShape_create();
    float scale_factor = 3.0f;

    sfConvexShape_setPointCount(shape, 4);
    sfConvexShape_setPoint(shape, 0, (sfVector2f){612.5f +
        scale_factor * (-62.5f), 550.0f + scale_factor * (-50.0f)});
    sfConvexShape_setPoint(shape, 1, (sfVector2f){612.5f +
        scale_factor * (87.5f), 550.0f + scale_factor * (-50.0f)});
    sfConvexShape_setPoint(shape, 2, (sfVector2f){612.5f +
        scale_factor * (87.5f), 550.0f + scale_factor * (50.0f)});
    sfConvexShape_setPoint(shape, 3, (sfVector2f){612.5f +
        scale_factor * (-112.5f), 550.0f + scale_factor * (50.0f)});
    sfConvexShape_setPosition(shape, position);
    sfConvexShape_setFillColor(shape, sfColor_fromRGBA(50, 50, 50, 240));
    sfRenderWindow_drawConvexShape(window, shape, NULL);
    sfConvexShape_destroy(shape);
}

static void draw_weapon_name(sfRenderWindow *window,
    sfFont *font, player_t *player, sfVector2f position)
{
    sfText *weapon_text = sfText_create();

    sfText_setString(weapon_text, player->weapon[player->actual_weapon].name);
    sfText_setFont(weapon_text, font);
    sfText_setCharacterSize(weapon_text, 40);
    sfText_setColor(weapon_text, sfWhite);
    sfText_setPosition(weapon_text,
        (sfVector2f){position.x + 500, position.y + 420});
    sfRenderWindow_drawText(window, weapon_text, NULL);
    sfText_destroy(weapon_text);
}

static void draw_ammo_count(sfRenderWindow *window,
    sfFont *font, player_t *player, sfVector2f position)
{
    sfText *ammo_text = sfText_create();
    char balles[256];

    snprintf(balles, sizeof(balles),
    "%d/%d", player->weapon[player->actual_weapon].munitions,
    player->weapon[player->actual_weapon].max_munitions);
    sfText_setString(ammo_text, balles);
    sfText_setFont(ammo_text, font);
    sfText_setCharacterSize(ammo_text, (strlen(balles) > 5) ?
    300 / strlen(balles) : 60);
    sfText_setColor(ammo_text, sfWhite);
    sfText_setPosition(ammo_text, (sfVector2f){position.x + 430,
        position.y + 500});
    sfRenderWindow_drawText(window, ammo_text, NULL);
    sfText_destroy(ammo_text);
}

void draw_amunitions(sfRenderWindow *window, player_t *player)
{
    sfVector2u windows_size = sfRenderWindow_getSize(window);
    sfVector2f position = {windows_size.x / (windows_size.y / 2.0f) + 1220,
        windows_size.y / (windows_size.y / 2.0f) + 480};
    sfFont *font = load_font();

    draw_ammo_background(window, position);
    draw_weapon_name(window, font, player, position);
    draw_ammo_count(window, font, player, position);
}
