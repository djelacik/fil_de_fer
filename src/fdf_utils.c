/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:21:44 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/16 12:11:04 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	close_window(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(mlx);
}

void	apply_isometrics(t_point *point, t_map *map)
{
	double	x;
	double	y;
	double	z;
	double	tmp;

	x = point->x;
	y = point->y;
	z = point->z;
	tmp = y * cos(map->rotation_x) - z * sin(map->rotation_x);
	z = y * sin(map->rotation_x) + z * cos(map->rotation_x);
	y = tmp;
	tmp = x * cos(map->rotation_y) + z * sin(map->rotation_y);
	z = -x * sin(map->rotation_y) + z * cos(map->rotation_y);
	x = tmp;
	tmp = x * cos(map->rotation_z) - y * sin(map->rotation_z);
	y = x * sin(map->rotation_z) + y * cos(map->rotation_z);
	x = tmp;
	tmp = (x - y) * cos(ANGLE);
	y = -z + (x + y) * sin(ANGLE);
	x = tmp;
	point->x = x;
	point->y = y;
}

void	multiply_z(t_map *map, double multiplier)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->map[y][x].z *= multiplier;
			x++;
		}
		y++;
	}
	map->z_scale = 1;
}

int	check_name(char *filename)
{
	int		len;
	int		i;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5)
		return (0);
	i = len - 4;
	if (filename[i] == '.' && filename[i + 1] == 'f'
		&& filename[i + 2] == 'd' && filename[i + 3] == 'f')
		return (1);
	return (0);
}

uint32_t	color_to_uint32(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}
