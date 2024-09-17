/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:04:23 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/17 22:25:13 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_line(mlx_image_t *img, t_points points, uint32_t color)
{
	t_draw	draw;

	initialize_draw(&draw, &points);
	printf("Initialized: dx = %d, dy = %d, sx = %d, sy = %d, err = %d\n",
		draw.dx, draw.dy, draw.sx, draw.sy, draw.err);
	while (42)
	{
		printf("Drawing at (%d, %d)\n", points.x0, points.y0);
		if (points.x0 >= 0 && points.x0 < WIDTH
				&& points.y0 >= 0 && points.y0 < HEIGHT)
			mlx_put_pixel(img, points.x0, points.y0, color);
		if (points.x0 == points.x1 && points.y0 == points.y1)
			break ;
		draw.e2 = 2 * draw.err;
		//if (draw.e2 >= draw.dy && draw.dx != 0)
		if (draw.e2 > -draw.dy)
		{
			draw.err -= draw.dy;
			points.x0 += draw.sx;
			printf("Updated x: %d\n", points.x0);
		}
		if (draw.e2 < draw.dx)
		{
			draw.err += draw.dx;
			points.y0 += draw.sy;
			printf("Updated y: %d (sy = %d)\n", points.y0, draw.sy);
		}
	}
}
