/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:36:28 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/02 10:44:20 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_color	interpolate_color(t_color start_clr, t_color end_clr, double fraction)
{
	t_color		result;
	
	result.r = (int)(start_clr.r + (end_clr.r - start_clr.r) * fraction);
	result.g = (int)(start_clr.g + (end_clr.g - start_clr.g) * fraction);
	result.b = (int)(start_clr.b + (end_clr.b - start_clr.b) * fraction);
	result.a = (int)(start_clr.a + (end_clr.a - start_clr.a) * fraction);
	return (result);
}

static uint32_t	color_to_uint32(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}

uint32_t	get_color(t_color start_color, t_color end_color, int i, double x)
{
	t_color		interpolated_color;
	double		fraction;
	
	fraction = ((double)i / fabs(x));
	interpolated_color = interpolate_color(start_color, end_color, fraction);
	return (color_to_uint32(interpolated_color));
}

t_color	color_based_on_height(double z, t_map *map)
{
	t_color		color;
	double		ratio;

	ratio = (z - map->min_z) / (map->max_z - map->min_z);
	
	//Base colors set here
	color.r = (int)(255 * ratio);
	color.g = (int)(255 * (1 - ratio));
	color.b = 0;
	color.a = 255;
	return (color);
}
