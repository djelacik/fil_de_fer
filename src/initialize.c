/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:15:48 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/13 17:47:45 by djelacik         ###   ########.fr       */
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

void	init_points(t_points *points, t_point start, t_point end, t_map *map)
{
	int sx = (int)start.y;
    int sy = (int)start.x;
    int ex = (int)end.y;
    int ey = (int)end.x;
	points->start.x = start.x;
	points->start.y = start.y;
	points->start.z = map->map[(int)start.y][(int)start.x].z / map->z_scale;
	points->end.x = end.x;
	points->end.y = end.y;
	points->end.z = map->map[(int)end.y][(int)end.x].z / map->z_scale;
	if (!map->has_any_color)
		points->s_color = color_based_on_height(points->start.z, map);
	else
		points->s_color = map->map[sx][sy].color;
	if (!map->has_any_color)
		points->e_color = color_based_on_height(points->end.z, map);
	else
		points->e_color = map->map[ex][ey].color;
	apply_isometrics(&points->start);
	apply_isometrics(&points->end);
}
