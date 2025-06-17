/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

float perlin_noise(float x, float y)
{
    float random_factor = ((float)rand() / RAND_MAX) * 0.1f;

    return fabs(sin(x * 10.0 + random_factor) * cos(y * 10.0 + random_factor));
}

void random_bouble(int y, int **generated_map)
{
    float noise;

    for (int x = 0; x < MAP_WIDTH; x++) {
        if (y == 0 || y == MAP_HEIGHT - 1
            || x == 0 || x == MAP_WIDTH - 1) {
            generated_map[y][x] = 1;
        } else {
            noise = perlin_noise((float)x
            / MAP_WIDTH, (float)y / MAP_HEIGHT);
            generated_map[y][x] = (noise > 0.5) ? 1 : 0;
        }
    }
}

int **generate_random_map(void)
{
    int **generated_map = malloc(sizeof(int *) * MAP_HEIGHT);

    if (!generated_map)
        exit(84);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        generated_map[y] = malloc(sizeof(int) * MAP_WIDTH);
        if (!generated_map[y])
            exit(84);
        random_bouble(y, generated_map);
    }
    return generated_map;
}
