##
## EPITECH PROJECT, 2024
## makefile
## File description:
## task1
##

NAME = wolf3d

SRC = src/main.c \
	src/events/events.c \
	src/events/keyboard.c \
	src/events/manette.c \
	src/events/mouse.c \
	src/draw/floor_ceiling.c \
	src/draw/player.c \
	src/maps/map.c \
	src/draw/draw_minimap.c \
	src/shoot.c \
	src/draw/draw_cursor.c \
	src/draw/objets.c \
	src/detect.c \
	src/events/aptic.c \
	src/draw/draw_statistics.c \
	src/events/process_objects.c \
	src/draw/draw_hud.c \
	src/menu/menu.c \
	src/menu/sprites.c \
	src/menu/buttons.c \
	src/backup/save.c \
	src/menu/dead.c \
	src/events/object_ai.c \
	src/draw/draw_gun.c \
	src/draw/cast_ray.c \
	src/draw/remove_obj.c \
	src/draw/draw_bar.c \
	src/menu/sprites_2.c \
	src/menu/credits.c \
	src/menu/sprites_3.c \
	src/menu/sprites_4.c \
	src/menu/settings.c \
	src/menu/settings_effect.c \
	src/draw/particles.c \
	src/menu/sprites_5.c \
	src/draw/draw_health_bar.c \
	src/draw/draw_settings.c \
	src/free.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -Wextra -I./include \
    -I./garbage_collector/include \
    -lm -W -Wall -Wextra

LDFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	gcc -c $< -o $@ $(CFLAGS)


$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) src/fake_bonus.c

bonus: $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) bonus/manage.c \
	bonus/connect.c

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f profile.txt
	rm -f *.out

re: fclean all

analyse: CFLAGS += -pg
analyse: re
	./wolf3d y
	gprof ./wolf3d gmon.out > profile.txt

debug: CFLAGS += -g
debug: re
	valgrind ./$(NAME)
