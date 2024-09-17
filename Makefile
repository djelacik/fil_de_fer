# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 19:04:37 by djelacik          #+#    #+#              #
#    Updated: 2024/09/17 21:17:55 by djelacik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I./MLX42/include
LDFLAGS = -L./MLX42 -lmlx42 -ldl -lglfw -pthread -lm


SRC = \
src/draw_3d_grid.c \
src/draw_line.c \
src/initialize.c \
src/open_window.c \
src/fdf_utils.c 
#src/draw_grid.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
