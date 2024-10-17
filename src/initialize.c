/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:15:48 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/16 12:13:13 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	initialize_draw(t_draw *draw, t_points *points)
{
	draw->dx = fabs(points->end.x - points->start.x);
	draw->dy = fabs(points->end.y - points->start.y);
	if (points->start.x < points->end.x)
		draw->sx = 1;
	else
		draw->sx = -1;
	if (points->start.y < points->end.y)
		draw->sy = 1;
	else
		draw->sy = -1;
	if (draw->dx > draw->dy)
		draw->err = draw->dx / 2;
	else
		draw->err = -draw->dy / 2;
}

t_map	*initialize_map(mlx_t *mlx, char *filename)
{
	t_map	*map;

	map = save_map(mlx, filename);
	if (!map)
	{
		ft_putstr_fd("Error saving the map\n", STDERR_FILENO);
		return (NULL);
	}
	find_max_min_z(map);
	z_scale(map);
	save_map_size(map);
	map_scale(map);
	apply_colors(map);
	map->zoom = 1.0;
	return (map);
}

mlx_t	*initalize_mlx(const char *filename)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, filename, true);
	if (!mlx)
	{
		ft_putstr_fd("Failed to initialize MLX\n", STDERR_FILENO);
		return (NULL);
	}
	return (mlx);
}

static void	get_colors(t_points *points, t_map *map, t_point start, t_point end)
{
	int	sx;
	int	sy;
	int	ex;
	int	ey;

	sx = (int)start.y;
	sy = (int)start.x;
	ex = (int)end.y;
	ey = (int)end.x;
	if (!map->has_any_color)
	{
		points->s_color = color_on_height(start.z, map);
		points->e_color = color_on_height(end.z, map);
	}
	else
	{
		points->s_color = map->map[sx][sy].color;
		points->e_color = map->map[ex][ey].color;
	}
}

void	init_points(t_points *points, t_point start, t_point end, t_map *map)
{
	double	z_start;
	double	z_end;

	z_start = map->map[(int)start.y][(int)start.x].z / map->z_scale;
	z_end = map->map[(int)end.y][(int)end.x].z / map->z_scale;
	start.z = z_start;
	end.z = z_end;
	get_colors(points, map, start, end);
	points->start = start;
	points->end = end;
	points->start.x *= map->zoom;
	points->start.y *= map->zoom;
	points->start.z *= map->zoom;
	points->end.x *= map->zoom;
	points->end.y *= map->zoom;
	points->end.z *= map->zoom;
	apply_isometrics(&points->start, map);
	apply_isometrics(&points->end, map);
	points->start.x += map->x_offset;
	points->start.y += map->y_offset;
	points->end.x += map->x_offset;
	points->end.y += map->y_offset;
}
