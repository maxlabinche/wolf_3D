/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"

int is_wall(int x, int y, int **map)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return 1;
    if ((map[y][x]) == 1)
        return 1;
    return 0;
}

int float_size(float value)
{
    int size = 0;

    if (value < 0) {
        value *= -1;
        size++;
    }
    while (value >= 1) {
        value /= 10;
        size++;
    }
    return (size + 1);
}

int int_size(int value)
{
    int size = 0;

    if (value < 0) {
        value *= -1;
        size++;
    }
    while (value >= 1) {
        value /= 10;
        size++;
    }
    return (size + 1);
}
