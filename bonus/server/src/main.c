/*
** EPITECH PROJECT, 2024
** my_putchar
** File description:
** print a character
*/
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include "../include/http.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

void handle_sigint(int sig)
{
    printf("\nCtrl+C détecté. Exit... (%d)\n", sig);
    exit(0);
}

int main(void)
{
    server_t *server = malloc(sizeof(server_t));
    pthread_t cleanup_thread;

    signal(SIGINT, handle_sigint);
    server->users = malloc(sizeof(users_t));
    init_server(server);

    if (pthread_create(&cleanup_thread, NULL, periodic_user_cleanup, server) != 0) {
        perror("Failed to create cleanup thread");
    }
    pthread_detach(cleanup_thread);
    all_sockets(server);
    free(server->network);
    return 0;
}
