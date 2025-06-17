/*
** EPITECH PROJECT, 2025
** garbage.c
** File description:
** This code is a garbage collector
*/
#include "garbage.h"

void *gc_malloc(garbage_t **garbage, size_t size)
{
    garbage_t *new = malloc(sizeof(garbage_t));

    if (new == NULL)
        return (NULL);
    new->ptr = malloc(size);
    if (new->ptr == NULL) {
        free(new);
        return (NULL);
    }
    new->next = *garbage;
    *garbage = new;
    return (new->ptr);
}

static void gc_free_condition(garbage_t **garbage,
    garbage_t *tmp, garbage_t *prev)
{
    if (tmp->ptr != NULL)
        free(tmp->ptr);
    if (prev == NULL)
        *garbage = tmp->next;
    else
        prev->next = tmp->next;
    free(tmp);
}

void *gc_free(garbage_t **garbage, void *ptr)
{
    garbage_t *tmp = *garbage;
    garbage_t *prev = NULL;

    while (tmp != NULL) {
        if (tmp->ptr == ptr) {
            gc_free_condition(garbage, tmp, prev);
            return (NULL);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (NULL);
}

void gc_collect(garbage_t **garbage)
{
    garbage_t *tmp = *garbage;
    garbage_t *prev = NULL;

    while (tmp != NULL) {
        if (tmp->ptr)
            free(tmp->ptr);
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    *garbage = NULL;
}

void *gc_custom(garbage_t **garbage, void *new_malloc)
{
    garbage_t *new = malloc(sizeof(garbage_t));

    if (new == NULL)
        return (NULL);
    new->ptr = new_malloc;
    if (new->ptr == NULL) {
        free(new);
        return (NULL);
    }
    new->next = *garbage;
    *garbage = new;
    return (new->ptr);
}
