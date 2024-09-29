/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:12:50 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/29 15:57:09 by djelacik         ###   ########.fr       */
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
}	t_draw;

typedef struct	s_point
{
	double			x;
	double			y;
	double			z;
}	t_point;

typedef struct	s_points
{
	t_point		start;
	t_point		end;
}	t_points;

typedef struct s_map
{
	int			**map;
	int			width;
	int			height;
	int			max_z;
	int			min_z;
	double		z_scale;
	double		size_scale;
	int			max_map_size;
	int			min_map_size;
}	t_map;

void	close_window(mlx_key_data_t keydata, void* param);
void	free_map_memory(t_map *map_data);
int		apply_height(int y, int z);
void	apply_isometrics(t_point *point);

void	initialize_draw(t_draw *draw, t_points *points);
void	init_points(t_points *points, t_point start, t_point end, t_map *map);
void	draw_line(mlx_image_t *img, t_points points, uint32_t color, t_map *map);

t_map	*save_map(const char *filename);
void	find_max_min_z(t_map *map);
void	save_map_size(t_map *map);
void	draw_map(mlx_image_t *img, t_map *map);
void	map_scale(t_map *map);

#endif
