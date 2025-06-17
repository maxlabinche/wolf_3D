/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** particles
*/

#include "palwish.h"

void init_particle_system(game_t *game)
{
    game->particles = malloc(sizeof(particle_system_t));
    game->particles->max_particles = 1000;
    game->particles->active_particles = 0;
    game->particles->particles = malloc(sizeof(particle_t)
        * game->particles->max_particles);
    for (int i = 0; i < game->particles->max_particles; i++)
        game->particles->particles[i].active = false;
}

static void setup_particle(particle_t *p, game_t *game)
{
    float random_angle = 0;
    float random_velocity = 0;

    p->position.x = 1920 / 2;
    p->position.y = 1080 / 2;
    p->active = true;
    random_angle = ((float)rand() / RAND_MAX) * 2 * M_PI;
    random_velocity = (30.0f + ((float)rand() / RAND_MAX) * 12.0f);
    p->velocity.x = cosf(random_angle) * random_velocity;
    p->velocity.y = sinf(random_angle) * random_velocity;
    p->color = sfColor_fromRGB(255, (rand() % 55), (rand() % 55));
    p->lifetime = 1.0f;
    p->size = 3.0f + ((float)rand() / RAND_MAX) * 3.0f;
    p->distance = 1.0f;
    game->particles->active_particles++;
}

void spawn_object_hit_particles(game_t *game)
{
    int particles_spawned = 0;
    particle_t *p = NULL;

    for (int i = 0; i < game->particles->max_particles
        && particles_spawned < 20; i++) {
        if (!game->particles->particles[i].active) {
            p = &game->particles->particles[i];
            setup_particle(p, game);
            particles_spawned++;
        }
    }
}

// add delta time
void update_particles(particle_system_t *ps, float delta_time)
{
    int active_count = 0;
    particle_t *p = NULL;
    sfColor color;

    for (int i = 0; i < ps->max_particles; i++) {
        p = &ps->particles[i];
        if (!p->active)
            continue;
        p->position.x += p->velocity.x * delta_time;
        p->position.y += p->velocity.y * delta_time;
        p->lifetime -= delta_time;
        color = p->color;
        color.a = (sfUint8)(255.0f * (p->lifetime / 0.3f));
        p->color = color;
        if (p->lifetime <= 0) {
            p->active = false;
        } else
            active_count++;
    }
    ps->active_particles = active_count;
}

void draw_particles(sfRenderWindow *window, particle_system_t *ps)
{
    sfCircleShape *particle_shape = sfCircleShape_create();
    particle_t *p = NULL;

    for (int i = 0; i < ps->active_particles; i++) {
        p = &ps->particles[i];
        if (!p->active)
            continue;
        sfCircleShape_setRadius(particle_shape, p->size);
        sfCircleShape_setOrigin(particle_shape,
            (sfVector2f){p->size, p->size});
        sfCircleShape_setPosition(particle_shape, p->position);
        sfCircleShape_setFillColor(particle_shape, p->color);
        sfRenderWindow_drawCircleShape(window, particle_shape, NULL);
    }
    sfCircleShape_destroy(particle_shape);
}

void cleanup_particle_system(game_t *game)
{
    if (game->particles) {
        free(game->particles->particles);
        free(game->particles);
    }
}
