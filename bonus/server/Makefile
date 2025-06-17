##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for setting up the project
##

NAME = workguard
DEBUG = -Wall -Wextra -Werror -g3
OPTIMISATION = -O3 -Ofast -march=native -flto \
	-funroll-loops -fomit-frame-pointer -Iinclude

all: $(NAME)

$(NAME):
	gcc src/main.c \
	src/modules/http/epollo.c \
	src/modules/http/http.c \
	src/modules/http/socket.c \
	src/modules/http/utils.c \
	src/modules/http/client.c \
	src/modules/http/client_events.c \
	-o $(NAME)

debug: fclean
	gcc src/*.c src/modules/http/*.c -o $(NAME) $(DEBUG)

clean:
	rm -f a.out
	rm -f $(NAME)

fclean: clean
	-rm -f *.gcov
	-rm -f *.gcda
	-rm -f *.gcno
	-rm -f *.out
	-rm -f unit_tests
	-rm -f coverage.json
	-rm -rf lmdb
	-rm -f test

re : fclean all
