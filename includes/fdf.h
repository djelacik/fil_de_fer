/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:12:50 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/13 19:02:12 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

#define WIDTH 1200
#define HEIGHT 800
//#define SCALE 400 / map->max_map_size

typedef struct	s_draw
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			i;
}	t_draw;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
	int		a;
}	t_color;

typedef struct	s_point
{
	double			x;
	double			y;
	double			z;
	t_color			color;
	int				has_color;
}	t_point;

typedef struct	s_points
{
	t_point		start;
	t_point		end;
	t_color		s_color;
	t_color		e_color;
}	t_points;

typedef struct s_map
{
	t_point		**map;
	int			width;
	int			height;
	float		max_z;
	float		min_z;
	double		z_scale;
	double		size_scale;
	int			max_map_size;
	int			min_map_size;
	int			has_any_color;
	double		x_offset;
	double		y_offset;
}	t_map;



void		close_window(mlx_key_data_t keydata, void* param);
void		free_map_memory(t_map *map_data);
int			apply_height(int y, int z);
void		apply_isometrics(t_point *point);

void		initialize_draw(t_draw *draw, t_points *points);
void		init_points(t_points *points, t_point start, t_point end, t_map *map);
void		draw_line(mlx_image_t *img, t_points points, t_map *map);
uint32_t	get_color(t_color start_color, t_color end_color, int i, double x);
t_color		color_based_on_height(double z, t_map *map);
t_color		hex_to_color(char *hex_str);
void 		apply_colors(t_map *map);
int	fill_row(t_point *row, char *line, t_map *map);

t_map		*save_map(const char *filename);
void		find_max_min_z(t_map *map);
void		save_map_size(t_map *map);
void		draw_map(mlx_image_t *img, t_map *map);
void		map_scale(t_map *map);


#endif
