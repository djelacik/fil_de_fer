/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:15:48 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/25 19:51:08 by djelacik         ###   ########.fr       */
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
	printf("Initialized draw: dx = %d, dy = %d, sx = %d, sy = %d, err = %d\n",
           draw->dx, draw->dy, draw->sx, draw->sy, draw->err);
}

void	init_points(t_points *points, t_point start, t_point end, t_map *map)
{
	points->start.x = start.x;
	points->start.y = start.y;
	points->start.z = map->map[start.y][start.x];
	points->end.x = end.x;
	points->end.y = end.y;
	points->end.z = map->map[end.y][end.x];

	printf("Before apply_height: Start: (%d, %d, %d), End: (%d, %d, %d)\n",
           points->start.x, points->start.y, points->start.z, 
           points->end.x, points->end.y, points->end.z);
		   
	// points->start.y = apply_height(points->start.y, points->start.z);
	// points->end.y = apply_height(points->end.y, points->end.z);

	printf("After apply_height: Start: (%d, %d), End: (%d, %d)\n",
           points->start.x, points->start.y, points->end.x, points->end.y);

	apply_isometrics(&points->start);
	apply_isometrics(&points->end);
	
	printf("After isometric: Start: (%d, %d), End: (%d, %d)\n",
           points->start.x, points->start.y, points->end.x, points->end.y);
}
