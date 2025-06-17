/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_bar
*/

#include "palwish.h"

static void draw_rectangle_round(sfRenderWindow *window,
    sfFloatRect rect,
    float radius,
    sfColor color)
{
    sfRectangleShape *h = sfRectangleShape_create();
    sfRectangleShape *v = sfRectangleShape_create();

    sfRectangleShape_setSize(h, (sfVector2f){rect.width
        - 2 * radius, rect.height});
    sfRectangleShape_setPosition(h, (sfVector2f){rect.left
        + radius, rect.top});
    sfRectangleShape_setFillColor(h, color);
    sfRenderWindow_drawRectangleShape(window, h, NULL);
    sfRectangleShape_destroy(h);
    sfRectangleShape_setSize(v, (sfVector2f){rect.width,
        rect.height - 2 * radius});
    sfRectangleShape_setPosition(v, (sfVector2f){rect.left,
        rect.top + radius});
    sfRectangleShape_setFillColor(v, color);
    sfRenderWindow_drawRectangleShape(window, v, NULL);
    sfRectangleShape_destroy(v);
}

static void draw_rectangle_angle(sfRenderWindow *window,
    sfFloatRect rect,
    float radius,
    sfColor color)
{
    unsigned int CORNER_PTS = 30;
    sfCircleShape *c = sfCircleShape_create();
    float ox;
    float oy;

    for (int i = 0; i < 4; ++i) {
        sfCircleShape_setRadius(c, radius);
        sfCircleShape_setPointCount(c, CORNER_PTS);
        sfCircleShape_setFillColor(c, color);
        ox = (i & 1) ? rect.width - 2 * radius : 0.f;
        oy = (i & 2) ? rect.height - 2 * radius : 0.f;
        sfCircleShape_setPosition(c,
            (sfVector2f){rect.left + ox, rect.top + oy});
        sfRenderWindow_drawCircleShape(window, c, NULL);
    }
    sfCircleShape_destroy(c);
}

void draw_angle_rectangle(sfRenderWindow *window,
    sfFloatRect rect,
    float radius,
    sfColor color)
{
    draw_rectangle_round(window, rect, radius, color);
    draw_rectangle_angle(window, rect, radius, color);
}

void draw_hud_health_bar(sfRenderWindow *window, player_t *player)
{
    sfVector2u win = sfRenderWindow_getSize(window);
    float BAR_W = win.x * 0.25f;
    float BAR_H = win.y * 0.03f;
    float BORDER = BAR_H * 0.20f;
    float RADIUS = BAR_H * 0.10f;
    sfVector2f pos = { win.x / (win.y / 2.0f) + win.y * 0.03f,
        win.y / (win.y / 2.0f) + 970.f - win.y * 0.03f};
    float ratio = (float)player->health / (float)player->maw_health;
    sfFloatRect borderRect = {pos.x - BORDER, pos.y - BORDER,
        BAR_W + 2 * BORDER, BAR_H + 2 * BORDER};
    sfFloatRect barRect = {pos.x, pos.y, BAR_W * ratio, BAR_H};

    draw_angle_rectangle(window, borderRect, RADIUS + BORDER, sfBlack);
    draw_angle_rectangle(window, barRect, RADIUS, sfRed);
}

void draw_stamina_bar(sfRenderWindow *window, player_t *player)
{
    sfVector2u win = sfRenderWindow_getSize(window);
    float BAR_W = win.x * 0.25f;
    float BAR_H = win.y * 0.03f;
    float BORDER = BAR_H * 0.20f;
    float RADIUS = BAR_H * 0.10f;
    sfVector2f pos = {win.x / (win.y / 2.0f) + win.y * 0.03f,
        win.y / (win.y / 2.0f) + 1000.f};
    float ratio = (float)player->stamina / (float)player->maw_stamina;
    sfFloatRect borderRect = {pos.x - BORDER, pos.y - BORDER,
        BAR_W + 2 * BORDER, BAR_H + 2 * BORDER};
    sfFloatRect barRect = {pos.x, pos.y, BAR_W * ratio, BAR_H};

    draw_angle_rectangle(window, borderRect, RADIUS + BORDER, sfBlack);
    draw_angle_rectangle(window, barRect, RADIUS, sfBlue);
}
