/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** draw_minimap
*/

#include "palwish.h"

static sfTexture *texture_of_type(int type)
{
    sfTexture *texture;

    if (type == 0) {
        texture = load_player();
    }
    if (type == 1 || type != 0) {
        texture = load_enemi();
    }
    return texture;
}

static void set_object(game_t *game, network_user_t *netu,
    int index, int origine)
{
    game->objects[index].x = netu->x;
    game->objects[index].y = netu->y;
    game->objects[index].health = netu->life;
    game->objects[index].max_health = 5;
    game->objects[index].is_visible = true;
    game->objects[index].origine = origine;
}

void create_object(game_t *game, network_user_t *netu,
    bool send, int origine)
{
    int index = game->object_count;

    game->object_count++;
    game->objects = realloc(game->objects,
        sizeof(object_t) * game->object_count);
    if (!game->objects)
        exit(84);
    set_object(game, netu, index, origine);
    game->objects[index].user = netu->user;
    game->objects[index].type = netu->type;
    game->objects[index].has_changed = send;
    game->objects[index].sprite = sfSprite_create();
    game->objects[index].angle = 0.0f;
    game->objects[index].texture = texture_of_type(netu->type);
    sfSprite_setTexture(game->objects[index].sprite,
        game->objects[index].texture, sfTrue);
}

static void move_object(game_t *game,
    int index, network_user_t *netu)
{
    game->objects[index].x = netu->x;
    game->objects[index].y = netu->y;
    if (game->objects[index].health > netu->life)
        game->objects[index].health = netu->life;
    if (game->objects[index].health <= 0)
        game->objects[index].is_visible = false;
}

void create_object_or_move(game_t *game, network_user_t *netu)
{
    int index = get_index_object_by_user(game, netu->user);

    if (index == -1) {
        create_object(game, netu, false, 0);
    } else {
        move_object(game, index, netu);
    }
}

static void init_game_objects(game_t *game, int i)
{
    game->objects[i].health = 10.0f;
    game->objects[i].max_health = 10.0f;
    game->objects[i].type = 1;
    game->objects[i].origine = 1;
    game->objects[i].user = rand() % 9000 + 1000;
    game->objects[i].angle = 0.0f;
}

void init_objects(game_t *game)
{
    game->object_count = 10;
    game->objects = malloc(sizeof(object_t) * game->object_count);
    if (!game->objects)
        exit(84);
    for (int i = 0; i < game->object_count; i++) {
        memset(&game->objects[i], 0, sizeof(object_t));
        game->objects[i].x = (rand() + time(NULL)) % MAP_WIDTH;
        game->objects[i].y = (rand() + time(NULL)) % MAP_HEIGHT;
        game->objects[i].sprite = sfSprite_create();
        game->objects[i].is_visible = true;
        game->objects[i].has_changed = true;
        game->objects[i].texture = texture_of_type(1);
        sfSprite_setTexture(game->objects[i].sprite,
            game->objects[i].texture, sfTrue);
        init_game_objects(game, i);
    }
}

int is_object_visible(player_t *player,
    object_t object, int **map, float *distance)
{
    float dx = object.x - player->x;
    float dy = object.y - player->y;
    float angle_to_object = atan2(dy, dx);
    float step = 0.01;
    int map_x;
    int map_y;

    *distance = calculate_distance(dx, dy);
    for (float t = 0; t < *distance; t += step) {
        map_x = (int)(player->x + t * cos(angle_to_object));
        map_y = (int)(player->y + t * sin(angle_to_object));
        if (is_wall(map_x, map_y, map)) {
            *distance = -1;
            return 0;
        }
    }
    return 1;
}

static void draw_object(sfRenderWindow *window, object_t object,
    float relative_angle, float distance)
{
    float scale = TILE_SIZE / distance;
    sfVector2u window_size = sfRenderWindow_getSize(window);
    float screen_x = (window_size.x / 2) +
    relative_angle * (window_size.x / FOV);
    float size_scale = 1.2f * scale / TILE_SIZE;
    sfVector2u texture_size = sfTexture_getSize(object.texture);
    float sprite_height = texture_size.y * size_scale;
    float horizon = WINDOW_HEIGHT / 2.0f;
    float floor_level = horizon + (200.0f / distance);

    sfSprite_setScale(object.sprite, (sfVector2f){size_scale, size_scale});
    sfSprite_setPosition(object.sprite, (sfVector2f){
        screen_x - (texture_size.x * size_scale / 2),
        floor_level - (sprite_height / 2)
    });
    draw_health_bar(window, object, distance);
    sfRenderWindow_drawSprite(window, object.sprite, NULL);
}

void draw_objects(game_t *game, player_t *player)
{
    object_t *obj;
    float distance;
    float ray_angle;
    float relative_angle;

    for (int i = 0; i < game->object_count; i++) {
        obj = &game->objects[i];
        distance = calculate_distance(obj->x - player->x, obj->y - player->y);
        ray_angle = atan2(obj->y - player->y, obj->x - player->x);
        relative_angle = ray_angle - player->angle;
        while (relative_angle < - M_PI)
            relative_angle += 2 * M_PI;
        while (relative_angle > M_PI)
            relative_angle -= 2 * M_PI;
        if (fabs(relative_angle) < (FOV / 2)
    && is_object_visible(player, game->objects[i], game->map, &distance)
    && obj->health > 0 && obj->is_visible) {
            draw_object(game->window, *obj, relative_angle, distance);
        }
    }
}
