# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 11:20:49 by djelacik          #+#    #+#              #
#    Updated: 2024/11/01 15:46:14 by djelacik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIBMLX = ./MLX42
MLX_42 = $(LIBMLX)/build/libmlx42.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O2 -fPIE -I$(LIBMLX)/include -I./libft -I./get_next_line -I./include
LDFLAGS = -L$(LIBMLX)/build -lmlx42 -lglfw -pthread -lm -L./libft -lft -pie

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

# Rule for building the final executable
all: $(NAME)

# Compile the project and link it with libft and MLX42
$(NAME): $(OBJ) libft/libft.a $(MLX_42)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compile libft library with -fPIE
libft/libft.a:
	@make CFLAGS="-Wall -Wextra -Werror -fPIE" -C libft

# Clone MLX42 if it does not exist
mlx_clone: 
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

# Build the MLX42 library only if it hasn't been built yet
$(MLX_42): mlx_clone
	@if [ ! -f "$(MLX_42)" ]; then \
		echo "Building MLX42..."; \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	fi

# Compile object files from source
%.o: %.c $(MLX_42)
	$(CC) $(CFLAGS) -o $@ -c $<

# Clean object files
clean:
	rm -f $(OBJ)
	@make clean -C libft
	rm -rf $(LIBMLX)/build

# Full clean (removes executable and object files)
fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

# Rebuild everything
re: fclean all

# Bonus target to compile the bonus version without relinking
bonus: $(NAME)

.PHONY: all clean fclean re bonus mlx_clone
