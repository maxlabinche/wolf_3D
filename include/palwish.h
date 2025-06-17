/*
** EPITECH PROJECT, 2025
** world.h
** File description:
** world
*/

#ifndef WORLD_H
    #define WORLD_H
    #include "garbage.h"
    #include <SFML/Window.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <unistd.h>
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>
    #include <SFML/Config.h>
    #include <SFML/System/Export.h>
    #include <SFML/System/Sleep.h>
    #include <SFML/System/Time.h>
    #include <SFML/System/Types.h>
    #include <math.h>
    #include <time.h>
    #include "assets.h"
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define NUM_RAYS 1920
    #define MAX_DEPTH 80
    #define M_PI 3.14159265358979323846
    #define FOV (M_PI / 3)
    #define TILE_SIZE 64
    #define MAP_WIDTH 30
    #define MAP_HEIGHT 30
    #define NUM_KEYS 256
    #define MINIMAP_SCALE 0.06
    #define MINIMAP_PLAYER_SIZE 3
    #define MINIMAP_WIDTH (MAP_WIDTH * TILE_SIZE * MINIMAP_SCALE)
    #define MINIMAP_HEIGHT (MAP_HEIGHT * TILE_SIZE * MINIMAP_SCALE)
    #define MINIMAP_TILE_SIZE TILE_SIZE * MINIMAP_SCALE
    #define MINIMAP_OFFSET_X 0
    #define MINIMAP_OFFSET_Y 0
    #define SERVER_IP "45.88.180.52"
    #define SERVER_PORT 8070

typedef struct {
    float x;
    float y;
    sfTexture *texture;
    sfSprite *sprite;
    bool is_visible;
    float health;
    float max_health;
    int user;
    int type;
    int origine;
    bool has_changed;
    float angle;
} object_t;

typedef struct {
    bool keys[NUM_KEYS];
} input_t;

typedef struct winclean_s {
    garbage_t *garbage;
    int return_value;
} winclean_t;

typedef struct {
    sfTexture *texture;
    sfMusic *music;
    int munitions;
    int max_munitions;
    float damage;
    int max_damage;
    float fire_rate;
    int reload_time;
    int etat;
    int frame;
    char *name;
} weapon_t;

typedef struct {
    float x;
    float y;
    float angle;
    sfCircleShape *cursor;
    sfClock *shoot_clock;
    weapon_t *weapon;
    int actual_weapon;
    float speed;
    float health;
    int maw_health;
    float stamina;
    int maw_stamina;
    sfFont *font;
    sfClock *reload_clock;
    bool reloading;
    bool darkness_enabled;
    int **map;
} player_t;

typedef struct {
    sfTexture *wall_texture;
    sfTexture *floor_texture;
    sfTexture *ceiling_texture;
} textures_t;

typedef struct {
    sfVector2f position;
    sfVector2f velocity;
    sfColor color;
    float lifetime;
    float size;
    bool active;
    float distance;
} particle_t;

typedef struct {
    particle_t *particles;
    int max_particles;
    int active_particles;
} particle_system_t;

typedef struct {
    sfRenderWindow *window;
    sfClock *clock;
    sfClock *common;
    textures_t *textures;
    object_t *objects;
    sfMusic *pan;
    int **map;
    int object_count;
    int paused;
    int socket;
    double latency;
    bool offline;
    int whoami;
    int send_object;
    int receive_object;
    float delta_time;
    sfClock *delta_clock;
    player_t *player;
    sfMusic *menu_music;
    sfMusic *game_music;
    particle_system_t *particles;
} game_t;

typedef struct {
    player_t *player;
    game_t *game;
} thread_data_t;

typedef struct {
    int user;
    double x;
    double y;
    double life;
    int type;
} network_user_t;

typedef struct {
    float ray_x;
    float ray_y;
    float ray_dx;
    float ray_dy;
    int map_x;
    int map_y;
    float deltaDistX;
    float deltaDistY;
    float sideDistX;
    float sideDistY;
    int stepX;
    int stepY;
    float distance;
} ray_t;

typedef struct {
    int hit;
    float distance;
    int side;
} raycast_result_t;

typedef struct {
    float wall_height;
    float top;
    float texture_x;
    sfColor darkness;
} wall_render_data_t;

typedef struct settings_s {
    sfSprite *btn_1920;
    sfSprite *btn_full;
    float bar_x;
    float bar_y;
    float bar_w;
    float bar_h;
    float cursor_w;
    float cursor_h;
    float cursor_x;
    float min_x;
    float max_x;
    float volume;
    int dragging;
    float bar2_x;
    float bar2_y;
    float bar2_w;
    float bar2_h;
    float cursor2_w;
    float cursor2_h;
    float cursor2_x;
    float min2_x;
    float max2_x;
    float volume2;
    int dragging2;
} settings_t;

void init_player(player_t *player, int **map);
int is_wall(int x, int y, int **map);
void draw_floor_and_ceiling(player_t *player, game_t *game);
void handle_event(game_t *game, sfEvent event,
    input_t *input, player_t *player);
void draw_3d_view(game_t *game, player_t *player);
void apply_movement(player_t *player, input_t *input,
    game_t *game);
int **generate_random_map(void);
void handle_shooting(player_t *player, game_t *game, input_t *input);
void draw_minimap(sfRenderWindow *window, player_t *player, int **map);
void draw_cursor(sfRenderWindow *window, player_t *player);
void init_objects(game_t *game);
void draw_objects(game_t *game, player_t *player);
void move_objects_randomly(game_t *game, player_t *player);
void draw_gun(sfRenderWindow *window, player_t *player, game_t *game);
void handle_common(game_t *game, input_t *input);
void handle_joysticsk(game_t *game, player_t *player);
void shoot(game_t *game, player_t *player);
void handle_event_manette(input_t *input, player_t *player);
void vibrate(int time);
void connection(game_t *game);
void actualise_data(void *arg);
int get_index_object_by_user(game_t *game, int user);
void create_object_or_move(game_t *game, network_user_t *netu);
void show_statistics(game_t *game);
float calculate_depth(float distance, float angle);
float calculate_distance(float dx, float dy);
float calculate_relative_angle(float angle_to_object,
    float player_angle);
void draw_hud(sfRenderWindow *window, player_t *player);
void menu_loop(game_t *game);
void draw_hud(sfRenderWindow *window, player_t *player);
void draw_hud_health_bar(sfRenderWindow *window,
    player_t *player);
void draw_stamina_bar(sfRenderWindow *window,
    player_t *player);
void draw_amunitions(sfRenderWindow *window,
    player_t *player);
void reload_weapon(player_t *player, input_t *input);
int int_size(int value);
int float_size(float value);
sfSprite *load_sprite(const char *filename, const char *error_message);
sfSprite *load_bg(void);
sfSprite *load_start(void);
sfSprite *load_quit(void);
void setup_menu_buttons(sfSprite **start_button,
    sfSprite **quit_button);
void set_button_position(sfSprite *button, float x, float y);
void remove_dead_objects(game_t *game);
int is_object_visible(player_t *player,
    object_t object, int **map, float *distance);
void backup_objects(game_t *game);
void create_object(game_t *game, network_user_t *netu,
    bool send, int origine);
void load_backup(game_t *game);
void draw_dead_menu(game_t *game, player_t *player);
void draw_wall_slice(game_t *game, int i,
    float ray_angle, raycast_result_t res);
raycast_result_t cast_ray(player_t *player, float ray_angle);
void remove_dead_objects(game_t *game);
void draw_angle_rectangle(sfRenderWindow *window,
    sfFloatRect rect,
    float radius,
    sfColor color);
void setup_menu_buttons_2(sfSprite **credits,
    sfSprite **settings);
sfSprite *load_settings(void);
sfSprite *load_credits(void);
void set_credits_page(game_t *game, sfSprite *bg);
sfFont *load_font(void);
sfSoundBuffer *load_key_buffer_buffer(void);
sfTexture *load_wall(void);
sfTexture *load_ceiling(void);
sfTexture *load_player(void);
sfTexture *load_enemi(void);
sfMusic *load_pan_1(void);
sfTexture *load_arm_1_first(void);
sfTexture *load_arm_1_second(void);
sfTexture *load_arm_2_first(void);
sfTexture *load_arm_2_second(void);
void update_network(game_t *game, player_t *player);
void go_vibre_treads(void);
void init_game_bonus(game_t *game);
void setting_loop(game_t *game, sfSprite *bg);
void draw_settings_ui(game_t *game, sfSprite *bg, settings_t *s);
void handle_resolution_buttons(game_t *game, float mouse_x,
    float mouse_y, settings_t *s);
void init_slider1_settings(settings_t *s);
void init_slider2_settings(settings_t *s);
void init_particle_system(game_t *game);
void draw_particles(sfRenderWindow *window, particle_system_t *ps);
void update_particles(particle_system_t *ps, float delta_time);
void cleanup_particle_system(game_t *game);
void spawn_object_hit_particles(game_t *game);
void draw_health_bar(sfRenderWindow *window, object_t object,
    float distance);
void free_static_resources(void);
void free_game(game_t *game);
sfTexture *load_button_1920(void);
sfTexture *load_button_full(void);
void load_music_menu(game_t *game);
int destroy_game(game_t *game);
#endif /* WORLD_H */
