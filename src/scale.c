/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:20:20 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/15 18:38:22 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	find_max_min_z(t_map *map)
{
	int		x;
	int		y;

	map->max_z = map->map[0][0].z;
	map->min_z = map->map[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x].z > map->max_z)
				map->max_z = (double)map->map[y][x].z;
			if (map->map[y][x].z < map->min_z)
				map->min_z = (double)map->map[y][x].z;
			x++;
		}
		y++;
	}
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
	map->size_scale = HEIGHT * 0.9 / (smaller * sqrt(2)
			+ (larger - smaller) / sqrt(2));
}

void	z_scale(t_map *map)
{
	map->z_scale = (double)(ft_max(fabs(map->max_z), fabs(map->min_z)));
	if (map->z_scale == 0)
		map->z_scale = 1;
	map->max_z /= map->z_scale;
	map->min_z /= map->z_scale;
}
