/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:12:50 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/17 19:49:13 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define WIDTH 1200
# define HEIGHT 800
# define ANGLE 0.7
# define ERROR_MSG "Error\n"
# define FORMAT_ERR "Bruh...\n"
# define ARGC_ERR "Usage: <filename>.fdf\n"
# define EXIT_MSG "Fdf closed succesfully\n"

typedef struct s_draw
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			i;
}	t_draw;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}	t_color;

typedef struct s_point
{
	double			x;
	double			y;
	double			z;
	t_color			color;
	int				has_color;
}	t_point;

typedef struct s_points
{
	t_point		start;
	t_point		end;
	t_color		s_color;
	t_color		e_color;
}	t_points;

typedef struct s_map
{
	mlx_image_t	*img;
	t_point		**map;
	int			width;
	int			height;
	double		max_z;
	double		min_z;
	double		z_scale;
	double		size_scale;
	int			max_map_size;
	int			min_map_size;
	int			has_any_color;
	double		x_offset;
	double		y_offset;
	double		z_multiplier;

	double		rotation_x;
	double		rotation_y;
	double		rotation_z;

	double		zoom;
}	t_map;

typedef struct s_context
{
	mlx_t	*mlx;
	t_map	*map;
}	t_context;

void		close_window(mlx_key_data_t keydata, void *param);
void		free_map_memory(mlx_t *mlx, t_map *map);
void		apply_isometrics(t_point *point, t_map *map);
int			error_exit(mlx_t *mlx, t_map *map, char *message);

void		initialize_draw(t_draw *draw, t_points *points);
void		init_points(t_points *points, t_point start,
				t_point end, t_map *map);
void		draw_line(mlx_image_t *img, t_points points, t_map *map);
uint32_t	color_to_uint32(t_color color);
uint32_t	get_color(t_color start_color, t_color end_color, int i, double x);
t_color		color_on_height(double z, t_map *map);
t_color		hex_to_color(char *hex_str);
void		apply_colors(t_map *map);
int			fill_row(t_point *row, char *line, t_map *map);

int			check_name(char *filename);
void		find_max_min_z(t_map *map);
void		save_map_size(t_map *map);
void		draw_map(mlx_image_t *img, t_map *map);
void		redraw(mlx_t *mlx, t_map *map);
void		map_scale(t_map *map);
void		z_scale(t_map *map);
void		multiply_z(t_map *map, double multiplier);

t_map		*save_map(mlx_t *mlx, const char *filename);
t_map		*initialize_map(mlx_t *mlx, char *filename);
mlx_t		*initalize_mlx(const char *filename);

void		loop_hook(void *param);

#endif
