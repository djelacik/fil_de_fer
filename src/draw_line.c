/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:04:23 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/24 20:51:41 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	scale_and_offset(t_points *points)
{
	int		offset_x;
	int		offset_y;

	offset_x = WIDTH / 2;
	offset_y = HEIGHT / 2;
	points->start.x = points->start.x * SCALE + offset_x;
	points->start.y = points->start.y * SCALE + offset_y;
	points->end.x = points->end.x * SCALE + offset_x;
	points->end.y = points->end.y * SCALE + offset_y;

	printf("After scaling: Start: (%d, %d), End: (%d, %d)\n",
	       points->start.x, points->start.y, points->end.x, points->end.y);
}

void	draw_line(mlx_image_t *img, t_points points, t_map *map, uint32_t color)
{
	t_draw	draw;

	(void)map;
	printf("Original start: (%d, %d), end: (%d, %d)\n", 
        points.start.x, points.start.y, points.end.x, points.end.y);
		
	scale_and_offset(&points);
	
	printf("After scaling: Start: (%d, %d), End: (%d, %d)\n",
	       points.start.x, points.start.y, points.end.x, points.end.y);
		   
	initialize_draw(&draw, &points);
	printf("Initialized: dx = %d, dy = %d, sx = %d, sy = %d, err = %d\n",
		draw.dx, draw.dy, draw.sx, draw.sy, draw.err);
	while (42)
	{
		if (points.start.x >= 0 && points.start.x < WIDTH
				&& points.start.y >= 0 && points.start.y < HEIGHT)
		{
			mlx_put_pixel(img, points.start.x, points.start.y, color);
			//printf("Drawing at (%d, %d)\n", points.start.x, points.start.y);
		}
		if (points.start.x == points.end.x && points.start.y == points.end.y)
		{
			//printf("Reached end point: (%d, %d)\n", points.end.x, points.end.y);
			break ;
		}
		draw.e2 = 2 * draw.err;
		if (draw.e2 > -draw.dy)
		{
			draw.err -= draw.dy;
			points.start.x += draw.sx;
			if (points.start.x < 0 || points.start.x >= WIDTH)
			{
				printf("Getting out on break\n");
				break;
			}
			printf("Updated x: %d\n", points.start.x);
		}
		if (draw.e2 < draw.dx)
		{
			draw.err += draw.dx;
			points.start.y += draw.sy;
			if (points.start.y < 0 || points.start.y >= HEIGHT)
			{
				printf("Getting out on break\n");
				break;
			}
			printf("Updated y: %d\n", points.start.y);
		}
	}
}
