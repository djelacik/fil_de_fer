/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:15:48 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/24 16:22:38 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	initialize_draw(t_draw *draw, t_points *points)
{
	draw->dx = abs(points->end.x - points->start.x);
	draw->dy = abs(points->end.y - points->start.y);
	
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

void	init_points(t_points *points, t_point start, t_point end, t_map *map)
{
	points->start.x = start.x;
	points->start.y = apply_height(start.y, map->map[start.y][start.x]);
	points->end.x = end.x;
	points->end.y = apply_height(end.y, map->map[end.y][end.x]);
	apply_isometrics(&points->start.x, &points->start.y, map->map[start.y][start.x], map);
	apply_isometrics(&points->end.x, &points->end.y, map->map[end.y][end.x], map);
}
