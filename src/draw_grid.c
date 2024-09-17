/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:13:59 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/17 19:17:55 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_grid(mlx_image_t *img)
{
	t_points	points;
	int			x;
	int			y;

	y = 0;
	while(y <= HEIGHT)
	{
		points.x0 = 0;
		points.y0 = y;
		points.x1 = WIDTH;
		points.y1 = y;
		draw_line(img, points, 0xFF0000FF); // Piirretään vaakasuora viiva
		y += GRID_SIZE;
	}
	x = 0;
	while (x <= WIDTH)
	{
		points.x0 = x;
		points.y0 = 0;
		points.x1 = x;
		points.y1 = HEIGHT;
		draw_line(img, points, 0xFF0000FF); // Piirretään pystysuora viiva
		x += GRID_SIZE;
	}
}
