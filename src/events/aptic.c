/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/fb.h>
#include <linux/uinput.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <pthread.h>

void lunch_vibrate(struct ff_effect *effect, int fd, int time)
{
    struct input_event play;

    memset(&play, 0, sizeof(play));
    play.type = EV_FF;
    play.code = effect->id;
    play.value = 1;
    if (write(fd, &play, sizeof(play)) < 0) {
        perror("Erreur écriture effet");
        close(fd);
        return;
    }
    usleep(effect->replay.length * time);
    play.value = 0;
    if (write(fd, &play, sizeof(play)) < 0) {
        perror("Erreur écriture effet");
    }
}

void vibrate(int time)
{
    const char *device = "/dev/input/event24";
    int fd = open(device, O_RDWR);
    struct ff_effect effect;

    if (fd < 0) {
        return;
    }
    memset(&effect, 0, sizeof(effect));
    effect.type = FF_RUMBLE;
    effect.id = -1;
    effect.u.rumble.strong_magnitude = 0xffff;
    effect.u.rumble.weak_magnitude = 0xffff;
    effect.replay.length = time;
    effect.replay.delay = 0;
    if (ioctl(fd, EVIOCSFF, &effect) < 0)
        return;
    lunch_vibrate(&effect, fd, time);
    close(fd);
}
