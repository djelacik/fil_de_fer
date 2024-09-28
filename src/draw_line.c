/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:04:23 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/28 11:58:49 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	scale_and_offset(t_points *points)
{
	int		offset_x;
	int		offset_y;

	offset_x = WIDTH / 2;
	offset_y = HEIGHT / 2;

	printf("Before scaling: Start: (%f, %f), End: (%f, %f)\n",
           points->start.x, points->start.y, points->end.x, points->end.y);

	points->start.x = points->start.x * SCALE + offset_x;
	points->start.y = points->start.y * SCALE + offset_y;
	points->end.x = points->end.x * SCALE + offset_x;
	points->end.y = points->end.y * SCALE + offset_y;

	printf("After scaling: Start: (%f, %f), End: (%f, %f)\n",
	       points->start.x, points->start.y, points->end.x, points->end.y);
}

static void	slope_less(mlx_image_t *img, t_points *points, t_draw *draw, uint32_t color)
{
	int		p;
	int		i;
	double	x;
	double	y;
	
	p = 2 * abs(draw->dy) - (draw->dx);
	i = 0;
	x = points->start.x;
	y = points->start.y;
	while (i++ < abs(draw->dx))
	{
		mlx_put_pixel(img, x, y, color);
		//printf("Slope less: Drawing pixel at (%f, %f)\n", x, y);
		x += draw->sx;
		if (p < 0)
			p = p + 2 * abs(draw->dy);
		else
		{
			p = p + 2 * abs(draw->dy) - 2 * abs(draw->dx);
			y += draw->sy;
		}
	}
}

static void	slope_more(mlx_image_t *img, t_points *points, t_draw *draw, uint32_t color)
{
	int		p;
	int		i;
	double	x;
	double	y;
	
	p = 2 * abs(draw->dx) - (draw->dy);
	i = 0;
	x = points->start.x;
	y = points->start.y;
	while (i++ < abs(draw->dy))
	{
		mlx_put_pixel(img, x, y, color);
		//printf("Slope more: Drawing pixel at (%f, %f)\n", x, y);
		y += draw->sy;
		if (p < 0)
			p = p + 2 * abs(draw->dx);
		else
		{
			p = p + 2 * abs(draw->dx) - 2 * abs(draw->dy);
			y += draw->sx;
		}
	}
}

void	draw_line(mlx_image_t *img, t_points points, uint32_t color)
{
	t_draw	draw;

	scale_and_offset(&points);
	initialize_draw(&draw, &points);

	if (abs(draw.dx) > abs(draw.dy))
		slope_less(img, &points, &draw, color);
	else
		slope_more(img, &points, &draw, color);
}