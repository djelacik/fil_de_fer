/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:49:21 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/02 10:43:34 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	draw_horizontal_line(mlx_image_t *img, int x, int y, t_map *map)
{
	t_points	points;
	t_point		start;
	t_point		end;
	
	start.x = x;
	start.y = y;
	end.x = x + 1;
	end.y = y;
	init_points(&points, start, end, map);
	draw_line(img, points, map);
}

static void	draw_vertical_line(mlx_image_t *img, int x, int y, t_map *map)
{
	t_points	points;
	t_point		start;
	t_point		end;
	
	start.x = x;
	start.y = y;
	end.x = x;
	end.y = y + 1;
	init_points(&points, start, end, map);
	draw_line(img, points, map);
}

void	draw_map(mlx_image_t *img, t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
			{
				draw_horizontal_line(img, x, y, map);
			}
			if (y < map->height - 1)
			{
				draw_vertical_line(img, x, y, map);
			}
			x++;
		}
		y++;
	}
}
