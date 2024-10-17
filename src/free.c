/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:06:56 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/16 12:00:51 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	free_map_memory(mlx_t *mlx, t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	if (map->img)
		mlx_delete_image(mlx, map->img);
	free(map);
}

int	error_exit(mlx_t *mlx, t_map *map, char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	if (map)
		free_map_memory(mlx, map);
	if (mlx)
		mlx_terminate(mlx);
	return (EXIT_FAILURE);
}
