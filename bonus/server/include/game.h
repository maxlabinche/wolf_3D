/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** print a character
*/
#ifndef GAME_H
    #define GAME_H
typedef struct users_s {
    int type;
    float x;
    float y;
    float life;
    int fd;
    int socket;
    int updated;
} users_t;
void *periodic_user_cleanup(void *arg);
#endif
