/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:12:50 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/17 19:40:11 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define GRID_SIZE 25

typedef struct	s_draw
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_draw;

typedef struct	s_points
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_points;

void	close_window(mlx_key_data_t keydata, void* param);

void	initialize_draw(t_draw *draw, t_points *points);
void	draw_line(mlx_image_t *img, t_points points, uint32_t color);
void	draw_grid(mlx_image_t *img);

#endif
