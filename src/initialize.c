/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:15:48 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/17 21:54:55 by djelacik         ###   ########.fr       */
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
	if (draw->dx > draw->dy)
		draw->err = draw->dx / 2;
	else
		draw->err = -draw->dy / 2;
}
