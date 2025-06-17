/*
** EPITECH PROJECT, 2025
** palwish
** File description:
** main
*/

#include "palwish.h"

void game_update(game_t *game, player_t *player, input_t *input)
{
    sfEvent event;
    sfTime elapsed_time = sfClock_getElapsedTime(game->delta_clock);

    game->delta_time = sfTime_asSeconds(elapsed_time);
    sfClock_restart(game->delta_clock);
    move_objects_randomly(game, player);
    handle_event(game, event, input, player);
    apply_movement(player, input, game);
    update_network(game, player);
}

void game_render(game_t *game, player_t *player)
{
    draw_floor_and_ceiling(player, game);
    draw_3d_view(game, player);
    draw_minimap(game->window, player, game->map);
    draw_objects(game, player);
    show_statistics(game);
    draw_gun(game->window, player, game);
    update_particles(game->particles, game->delta_time);
    draw_particles(game->window, game->particles);
    draw_cursor(game->window, player);
    draw_hud(game->window, player);
    if (player->health <= 0) {
        draw_dead_menu(game, player);
    }
    sfRenderWindow_display(game->window);
}

void game_loop(game_t *game, player_t *player)
{
    input_t input = {0};

    if (game->menu_music)
        sfMusic_stop(game->menu_music);
    if (game->game_music)
        sfMusic_play(game->game_music);
    while (sfRenderWindow_isOpen(game->window)) {
        handle_common(game, &input);
        handle_joysticsk(game, player);
        game_update(game, player, &input);
        game_render(game, player);
        handle_shooting(player, game, &input);
    }
}

static void init_window_and_clocks(game_t *game)
{
    sfVideoMode desktop_mode = sfVideoMode_getDesktopMode();
    sfView *view;
    sfVector2u size = {1920, 1080};

    game->window = sfRenderWindow_create(
        desktop_mode, "Palwish", sfResize | sfClose | sfFullscreen, NULL);
    sfRenderWindow_setSize(game->window, size);
    if (!game->window)
        exit(84);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    view = sfView_create();
    sfView_setSize(view, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
    sfView_setCenter(view, (sfVector2f)
    {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f});
    sfRenderWindow_setView(game->window, view);
    game->clock = sfClock_create();
    game->common = sfClock_create();
    game->delta_clock = sfClock_create();
    game->delta_time = 0;
}

static void init_game_resources(game_t *game)
{
    game->textures = malloc(sizeof(textures_t));
    game->textures->wall_texture = load_wall();
    game->textures->ceiling_texture = load_ceiling();
    game->map = malloc(sizeof(int *) * MAP_HEIGHT);
    game->map = generate_random_map();
    if (!game->textures || !game->map)
        exit(84);
    init_objects(game);
    if (game->offline == true)
        load_backup(game);
    game->paused = 0;
    sfRenderWindow_setMouseCursorGrabbed(game->window, sfTrue);
    sfRenderWindow_setMouseCursorVisible(game->window, sfFalse);
}

void lunch_struct(game_t *game)
{
    load_music_menu(game);
    if (game->menu_music)
        sfMusic_play(game->menu_music);
    game->whoami = (rand() + time(NULL)) % 991 + 10;
    printf("Your ID is %d\n", game->whoami);
    init_window_and_clocks(game);
    init_particle_system(game);
    menu_loop(game);
    init_game_resources(game);
}

static int check_environment(void)
{
    char *display = getenv("DISPLAY");
    char *wayland = getenv("WAYLAND_DISPLAY");
    char *term = getenv("TERM");
    char *shell = getenv("SHELL");

    if (!display && !wayland) {
        fprintf(stderr, "Error: No display available\n");
        return 84;
    }
    if (!term && !shell) {
        fprintf(stderr, "Error: Missing essential environment variables\n");
        return 84;
    }
    return 0;
}

static int is_tty(void)
{
    if (!getenv("DISPLAY") && !getenv("WAYLAND_DISPLAY"))
        return 84;
    else
        return check_environment();
}

int main(int argc, char **argv)
{
    game_t *game = malloc(sizeof(game_t));
    player_t *player = malloc(sizeof(player_t));

    if (!game || !player || argc != 1 || is_tty() == 84
        || argv[1] != NULL)
        return 84;
    srand(time(NULL));
    init_game_bonus(game);
    lunch_struct(game);
    init_player(player, game->map);
    connection(game);
    game_loop(game, player);
    return destroy_game(game);
}
