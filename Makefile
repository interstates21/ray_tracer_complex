NAME = RTv1
PATH_SRC = ./
PATH_OBJ = ./
PATH_INC = ./inc

CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEAD = inc/rt.h

SRC =	main.c utils.c vector1.c vector2.c rotations.c render.c parse.c console_output.c intersect.c shader.c normals.c ft_atov3f.c parse_utils.c list.c parse_objects.c get_next_line.c controls.c
THREADS = -lpthread

OBJ = $(patsubst %.c,%.o,$(addprefix $(PATH_SRC), $(SRC)))


all: $(NAME)

$(NAME): $(OBJ) $(HEAD)
	make -C libft/
	$(CC) $(CFLAGS) -I $(PATH_INC) -c $(SRC)
	$(CC) -o $(NAME) $(OBJ) $(THREADS) -lm -L libft/ -lft -lmlx -framework OpenGL -framework AppKit

clean:
	make -C libft/ clean
	/bin/rm -rf *.o
	/bin/rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all re @(NAME)