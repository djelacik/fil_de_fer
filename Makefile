NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O2 -fPIE -I./MLX42/include -I./libft -I./get_next_line -I./include
LDFLAGS = -L./MLX42/build -lmlx42 -lglfw -pthread -lm -L./libft -lft -pie

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
$(NAME): $(OBJ) libft/libft.a MLX42/build/libmlx42.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

# Compile libft library with -fPIE
libft/libft.a:
	@make CFLAGS="-Wall -Wextra -Werror -fPIE" -C libft

# Build the MLX42 library for Linux
MLX42/build/libmlx42.a:
	cmake ./MLX42 -B ./MLX42/build
	make -C ./MLX42/build -j4

# Compile object files from source
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Clean object files
clean:
	rm -f $(OBJ)
	@make clean -C libft
	rm -rf ./MLX42/build

# Full clean (removes executable and object files)
fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

# Rebuild everything
re: fclean all

# Bonus target to compile the bonus version without relinking
bonus: $(NAME)

#$(NAME): $(OBJ) libft/libft.a MLX42/build/libmlx42.a
#$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

.PHONY: all clean fclean re bonus
