/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:20:20 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/29 17:51:28 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	find_max_min_z(t_map *map)
{
	int		x;
	int		y;

	map->max_z = map->map[0][0];
	map->min_z = map->map[0][0];
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] > map->max_z)
				map->max_z = map->map[y][x];
			if (map->map[y][x] < map->min_z)
				map->min_z = map->map[y][x];
			x++;
		}
		y++;
	}
	map->z_scale = (double)(ft_max(abs(map->max_z), abs(map->min_z)));
}

void	save_map_size(t_map *map)
{
	map->max_map_size = ft_max(map->height, map->width);
	map->min_map_size = ft_min(map->height, map->width);
}

void	map_scale(t_map *map)
{
	int		smaller;
	int		larger;

	smaller = ft_min(map->height, map->width);
	larger = ft_max(map->height, map->width);
	map->size_scale = HEIGHT * 0.9 / (smaller * sqrt(2) + (larger - smaller) / sqrt(2));
}

