/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:04:23 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/15 18:37:35 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	scale_and_offset(t_map *map, t_points *points)
{
	int		offset_x;
	int		offset_y;

	offset_x = WIDTH / 2 - (125 - (125 * map->min_map_size
				/ map->max_map_size));
	offset_y = HEIGHT / 10;
	points->start.x = points->start.x * map->size_scale + offset_x;
	points->start.y = points->start.y * map->size_scale + offset_y;
	points->end.x = points->end.x * map->size_scale + offset_x;
	points->end.y = points->end.y * map->size_scale + offset_y;
}

static void	slope_less(mlx_image_t *img, t_points *pts, t_draw *draw)
{
	int			p;
	double		x;
	double		y;
	uint32_t	color;

	p = 2 * abs(draw->dy) - (draw->dx);
	draw->i = 0;
	x = pts->start.x;
	y = pts->start.y;
	while (draw->i++ < abs(draw->dx))
	{
		color = get_color(pts->s_color, pts->e_color, draw->i, abs(draw->dx));
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, x, y, color);
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

static void	slope_more(mlx_image_t *img, t_points *pts, t_draw *draw)
{
	int			p;
	double		x;
	double		y;
	uint32_t	color;

	p = 2 * abs(draw->dx) - (draw->dy);
	draw->i = 0;
	x = pts->start.x;
	y = pts->start.y;
	while (draw->i++ < abs(draw->dy))
	{
		color = get_color(pts->s_color, pts->e_color, draw->i, abs(draw->dy));
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, x, y, color);
		y += draw->sy;
		if (p < 0)
			p = p + 2 * abs(draw->dx);
		else
		{
			p = p + 2 * abs(draw->dx) - 2 * abs(draw->dy);
			x += draw->sx;
		}
	}
}

void	draw_line(mlx_image_t *img, t_points points, t_map *map)
{
	t_draw	draw;

	scale_and_offset(map, &points);
	initialize_draw(&draw, &points);
	if (abs(draw.dx) > abs(draw.dy))
		slope_less(img, &points, &draw);
	else
		slope_more(img, &points, &draw);
}
