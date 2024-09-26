/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:21:44 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/25 19:52:53 by djelacik         ###   ########.fr       */
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

void	free_map_memory(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < map_data->height)
	{
		free(map_data->map[i]);
		i++;
	}
	free(map_data->map);
	free(map_data);
}

int	apply_height(int y, int z)
{
	return (y - (z * SCALE));
}

void	apply_isometrics(t_point *point)
{
	double		prev_x;
	double		prev_y;

	prev_x = point->x;
	prev_y = point->y;
	point->x = (prev_x - prev_y) * cos(0.523599);
	point->y = (prev_x + prev_y) * sin(0.523599) - point->z * 0.5;
}
