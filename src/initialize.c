/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:15:48 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/17 16:03:21 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	initialize_draw(t_draw *draw, t_points *points)
{
	draw->dx = abs(points->x1 - points->x0);
	draw->dy = abs(points->y1 - points->y0);
	
	if (points->x0 < points->x1)
		draw->sx = 1;
	else
		draw->sx = -1;
	if (points->y0 < points->y1)
		draw->sy = 1;
	else
		draw->sy = -1;
	draw->err = draw->dx + draw->dy; 
}
