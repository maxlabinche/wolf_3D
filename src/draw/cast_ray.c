/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"

static void init_ray(ray_t *ray, player_t *player, float ray_angle)
{
    ray->ray_x = player->x;
    ray->ray_y = player->y;
    ray->ray_dx = cosf(ray_angle);
    ray->ray_dy = sinf(ray_angle);
    ray->map_x = (int)ray->ray_x;
    ray->map_y = (int)ray->ray_y;
    ray->deltaDistX = fabsf(1.0f / ray->ray_dx);
    ray->deltaDistY = fabsf(1.0f / ray->ray_dy);
    ray->distance = 0.0f;
}

static void calculate_step_and_sidedist(ray_t *ray)
{
    if (ray->ray_dx < 0) {
        ray->stepX = -1;
        ray->sideDistX = (ray->ray_x - ray->map_x) * ray->deltaDistX;
    } else {
        ray->stepX = 1;
        ray->sideDistX = (ray->map_x + 1.0f - ray->ray_x) * ray->deltaDistX;
    }
    if (ray->ray_dy < 0) {
        ray->stepY = -1;
        ray->sideDistY = (ray->ray_y - ray->map_y) * ray->deltaDistY;
    } else {
        ray->stepY = 1;
        ray->sideDistY = (ray->map_y + 1.0f - ray->ray_y) * ray->deltaDistY;
    }
}

static void step_ray(ray_t *ray, int *side)
{
    if (ray->sideDistX < ray->sideDistY) {
        ray->sideDistX += ray->deltaDistX;
        ray->map_x += ray->stepX;
        *side = 0;
    } else {
        ray->sideDistY += ray->deltaDistY;
        ray->map_y += ray->stepY;
        *side = 1;
    }
}

static int check_hit(ray_t *ray, int **map, int side)
{
    if (ray->map_x >= 0 && ray->map_x < MAP_WIDTH &&
        ray->map_y >= 0 && ray->map_y < MAP_HEIGHT &&
        map[ray->map_y][ray->map_x] == 1) {
        if (side == 0)
            ray->distance = (ray->map_x - ray->ray_x +
    (1 - ray->stepX) / 2.0f) / ray->ray_dx;
        else
            ray->distance = (ray->map_y - ray->ray_y +
    (1 - ray->stepY) / 2.0f) / ray->ray_dy;
        return 1;
    }
    return 0;
}

static int perform_dda(ray_t *ray, int **map, int *side)
{
    int hit = 0;

    while (!hit && ray->distance < MAX_DEPTH) {
        step_ray(ray, side);
        hit = check_hit(ray, map, *side);
    }
    return hit;
}

raycast_result_t cast_ray(player_t *player, float ray_angle)
{
    ray_t ray;
    raycast_result_t result;

    init_ray(&ray, player, ray_angle);
    calculate_step_and_sidedist(&ray);
    result.hit = perform_dda(&ray, player->map, &result.side);
    result.distance = ray.distance;
    return result;
}
