/*
** EPITECH PROJECT, 2024
** garbage.h
** File description:
** my
*/

#ifndef GARBAGE_H
    #define GARBAGE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

typedef struct garbage_s {
    void *ptr;
    struct garbage_s *next;
} garbage_t;

void *gc_malloc(garbage_t **garbage, size_t size);
void *gc_free(garbage_t **garbage, void *ptr);
void gc_collect(garbage_t **garbage);
void *gc_realloc(void *ptr, size_t size, garbage_t **garbage);
void *gc_custom(garbage_t **garbage, void *new_malloc);
#endif
