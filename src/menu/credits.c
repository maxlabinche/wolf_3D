/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** Main menu loop and sprite loading functions
*/

#include "palwish.h"

char *get_full_str(void)
{
    char *full_str =
    "EPITECH 2025\n\n"
    "Palwish\n\n"
    "Developpe par:\n"
    "Pierric Buchez\n"
    "Mathis Brossier\n"
    "Maximilien lachevre--leconte\n\n"
    "Merci d'avoir joue !\n\n"
    "Cliquez pour revenir au menu.";

    return full_str;
}

int handle_events(game_t *game, sfEvent event)
{
    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(game->window);
        if ((event.type == sfEvtKeyPressed
            || event.type == sfEvtMouseButtonPressed)) {
            return 1;
        }
    }
    return 0;
}

static void update_text_buffer(char *buffer,
    const char *full_str, sfClock *clock,
    sfSound *key_sound)
{
    static int cur_char = 0;
    static float delay = 0.2f;

    if (cur_char < (int)strlen(full_str)) {
        if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) > delay) {
            buffer[cur_char] = full_str[cur_char];
            (cur_char)++;
            buffer[cur_char] = '\0';
            sfClock_restart(clock);
            sfSound_play(key_sound);
            delay = 0.05f + ((float)rand() / RAND_MAX) * 0.35f;
        }
    }
}

static void draw_credits_screen(game_t *game, sfSprite *bg, sfText *text)
{
    sfVector2u win_size = sfRenderWindow_getSize(game->window);
    sfFloatRect bounds = sfText_getLocalBounds(text);

    sfText_setPosition(text, (sfVector2f){
        (win_size.x - bounds.width) / 2,
        (win_size.y - bounds.height) / 2
    });
    sfSprite_setScale(bg, (sfVector2f){
        (float)win_size.x / sfTexture_getSize(sfSprite_getTexture(bg)).x,
        (float)win_size.y / sfTexture_getSize(sfSprite_getTexture(bg)).y
    });
    sfSprite_setPosition(bg, (sfVector2f){0, 0});
    sfRenderWindow_drawSprite(game->window, bg, NULL);
    sfRenderWindow_drawText(game->window, text, NULL);
    sfRenderWindow_display(game->window);
}

static void setup_text_and_sound(sfText **text, sfFont **font,
    sfSound **key_sound, sfSoundBuffer **key_buffer)
{
    *font = load_font();
    *text = sfText_create();
    *key_buffer = load_key_buffer_buffer();
    *key_sound = sfSound_create();
    sfText_setFont(*text, *font);
    sfText_setCharacterSize(*text, 48);
    sfText_setColor(*text, sfWhite);
    sfSound_setBuffer(*key_sound, *key_buffer);
}

void free_resources(sfText *text,
    sfSound *key_sound, sfSoundBuffer *key_buffer)
{
    sfText_destroy(text);
    sfSound_destroy(key_sound);
    sfSoundBuffer_destroy(key_buffer);
}

void set_credits_page(game_t *game, sfSprite *bg)
{
    sfEvent event;
    sfFont *font;
    sfText *text;
    sfSoundBuffer *key_buffer;
    sfSound *key_sound;
    char *full_str = get_full_str();
    char *buffer = calloc(strlen(full_str) + 2, 1);
    sfClock *clock = sfClock_create();

    setup_text_and_sound(&text, &font, &key_sound, &key_buffer);
    while (sfRenderWindow_isOpen(game->window)) {
        if (handle_events(game, event))
            break;
        update_text_buffer(buffer, full_str,
            clock, key_sound);
        sfText_setString(text, buffer);
        draw_credits_screen(game, bg, text);
    }
    free_resources(text, key_sound, key_buffer);
}
