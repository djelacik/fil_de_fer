# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 19:04:37 by djelacik          #+#    #+#              #
#    Updated: 2024/10/16 11:13:23 by djelacik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O2 -I./MLX42/include -I./libft -I./get_next_line 
LDFLAGS = -L./MLX42 -lmlx42 -ldl -lglfw -pthread -lm -L./libft -lft

SRC = \
src/draw_line.c \
src/initialize.c \
src/main.c \
src/fdf_utils.c \
src/save_map.c \
src/draw_map.c \
src/scale.c \
src/colors.c \
src/hooks.c \
src/free.c \
src/save_row.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

# Compile the project and link it with libft and MLX42
$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compile libft library
libft/libft.a:
	@make -C libft

# Clean object files
clean:
	rm -f $(OBJ)
	@make clean -C libft

# Full clean (removes executable and object files)
fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

# Rebuild everything
re: fclean all
