/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:56:16 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/18 14:37:58 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	handle_zoom(mlx_t *mlx, t_map *map)
{
	double	zoom_speed;

	zoom_speed = 0.01;
	if (mlx_is_key_down(mlx, MLX_KEY_Z))
	{
		map->zoom += zoom_speed;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_X))
	{
		map->zoom -= zoom_speed;
		if (map->zoom < 0.01)
			map->zoom = 0.01;
	}
}

static void	handle_rotation(mlx_t *mlx, t_map *map)
{
	double	rotation_speed;

	rotation_speed = 0.02;
	if (mlx_is_key_down(mlx, MLX_KEY_Q))
		map->rotation_x += rotation_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		map->rotation_x -= rotation_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		map->rotation_y += rotation_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		map->rotation_y -= rotation_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_E))
		map->rotation_z += rotation_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		map->rotation_z -= rotation_speed;
}

static void	handle_movement(mlx_t *mlx, t_map *map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		map->y_offset -= 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		map->y_offset += 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		map->x_offset -= 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		map->x_offset += 0.1;
}

static void	handle_scaling(mlx_t *mlx, t_map *map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
	{
		map->z_scale *= 0.99;
		find_max_min_z(map);
		map->max_z /= map->z_scale;
		map->min_z /= map->z_scale;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
	{
		map->z_scale *= 1.01;
		find_max_min_z(map);
		map->max_z /= map->z_scale;
		map->min_z /= map->z_scale;
	}
}

void	loop_hook(void *param)
{
	t_context	*context;
	mlx_t		*mlx;
	t_map		*map;

	context = (t_context *)param;
	mlx = context->mlx;
	map = context->map;
	handle_movement(mlx, map);
	handle_scaling(mlx, map);
	handle_rotation(mlx, map);
	handle_zoom(mlx, map);
	redraw(mlx, map);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
