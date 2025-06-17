/*
** EPITECH PROJECT, 2025
** garbage.c
** File description:
** This code is a garbage collector
*/
#include "garbage.h"
#include <stdio.h>

int main(void)
{
    int *array = gc_malloc(5 * sizeof(int));

    if (array == NULL)
        return (1);
    for (int i = 0; i < 5; i++)
        array[i] = i * 2;
    array = gc_realloc(array, 10 * sizeof(int));
    if (array == NULL)
        return (1);
    for (int i = 5; i < 10; i++)
        array[i] = i * 3;
    for (int i = 0; i < 10; i++)
        printf("array[%d] = %d\n", i, array[i]);
    gc_collect();
    return (0);
}
