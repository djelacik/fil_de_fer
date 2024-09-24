/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:21:44 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/24 20:55:44 by djelacik         ###   ########.fr       */
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

void	apply_isometrics(int *x, int *y, int z, t_map *map)
{
	int		prev_x = *x;
	int		prev_y = *y;

	(void)map;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
	*x = *x / SCALE + WIDTH / 2;
	*y = *y / SCALE + HEIGHT / 2;
}
