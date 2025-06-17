/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"

void draw_3d_view(game_t *game, player_t *player)
{
    float ray_angle = player->angle - (FOV / 2);
    float angle_step = FOV / NUM_RAYS;
    raycast_result_t res;

    game->player = player;
    for (int i = 0; i < NUM_RAYS; i++) {
        res = cast_ray(player, ray_angle);
        if (res.hit)
            draw_wall_slice(game, i, ray_angle, res);
        ray_angle += angle_step;
    }
}

static void init_ak47(player_t *player)
{
    player->weapon = malloc(sizeof(weapon_t) * 2);
    if (!player->weapon)
        exit(84);
    player->weapon[0].texture = load_arm_1_first();
    player->weapon[0].music = load_pan_1();
    player->weapon[0].max_munitions = 140;
    player->weapon[0].munitions = 140;
    player->weapon[0].damage = 0.5;
    player->weapon[0].fire_rate = 0.01;
    player->weapon[0].reload_time = 3;
    player->weapon[0].etat = 0;
    player->weapon[0].name = "AK47";
}

static void init_minigun(player_t *player)
{
    player->weapon[1].texture = load_arm_2_first();
    player->weapon[1].music = load_pan_1();
    player->weapon[1].max_munitions = 500;
    player->weapon[1].munitions = 500;
    player->weapon[1].damage = 0.3;
    player->weapon[1].fire_rate = 0.001;
    player->weapon[1].reload_time = 10;
    player->weapon[1].etat = 0;
    player->weapon[1].name = "MINIGUN";
}

void init_weapons(player_t *player)
{
    player->shoot_clock = sfClock_create();
    if (!player->shoot_clock)
        exit(84);
    player->actual_weapon = 0;
    init_ak47(player);
    init_minigun(player);
    if (!player->weapon[0].texture
        || !player->weapon[0].music)
        exit(84);
    if (!player->weapon[1].texture
        || !player->weapon[1].music)
        exit(84);
}

void generate_random_position_not_in_wall(int **map, player_t *player)
{
    player->x = rand() % MAP_WIDTH;
    player->y = rand() % MAP_HEIGHT;
    while (
        is_wall(player->x, player->y, map) ||
        is_wall(player->x - 1, player->y, map) ||
        is_wall(player->x + 1, player->y, map) ||
        is_wall(player->x, player->y - 1, map) ||
        is_wall(player->x, player->y + 1, map)
    ){
        player->x = rand() % MAP_WIDTH;
        player->y = rand() % MAP_HEIGHT;
    }
}

void init_player(player_t *player, int **map)
{
    generate_random_position_not_in_wall(map, player);
    player->angle = 0;
    player->speed = 1;
    player->health = 5;
    player->maw_health = 5;
    player->stamina = 100.0;
    player->maw_stamina = 100;
    player->cursor = sfCircleShape_create();
    player->reloading = false;
    player->reload_clock = sfClock_create();
    player->font = load_font();
    player->map = map;
    player->darkness_enabled = true;
    if (!player->font || !player->reload_clock)
        exit(84);
    init_weapons(player);
}
