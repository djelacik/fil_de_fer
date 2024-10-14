/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:36:28 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/14 13:37:18 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_color	interpolate_color(t_color start_clr, t_color end_clr, double fraction)
{
	t_color		result;
	
	result.r = (int)(start_clr.r + (end_clr.r - start_clr.r) * fraction);
	result.g = (int)(start_clr.g + (end_clr.g - start_clr.g) * fraction);
	result.b = (int)(start_clr.b + (end_clr.b - start_clr.b) * fraction);
	result.a = 255;
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
	//printf("Z: %f, Min_z: %f, Max_z: %f, Ratio: %f\n", z, map->min_z, map->max_z, ratio);

	//Base colors set here
	color.r = (int)(50 * (1 - ratio) + 255 * ratio);   // Punainen menee 0 -> 255
	color.g = (int)(0 * (1 - ratio) + 100 * ratio);   // Vihreä menee 0 -> 255
	color.b = (int)(255 * (1 - ratio) + 255 * ratio);
	color.a = 255;
	return (color);
}

t_color	hex_to_color(char *hex_str)
{
	t_color		color;
	uint32_t 	hex_value;
	int			i;

	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		hex_str += 2;
	i = -1;
	while (hex_str[i++])
		hex_str[i] = ft_tolower(hex_str[i]);
	hex_value = ft_atoi_base(hex_str, "0123456789abcdef");
	color.r = (hex_value >> 16) & 0xFF;
	color.g = (hex_value >> 8) & 0xFF;
	color.b = hex_value & 0xFF;
	color.a = 255;
	return (color);
}

void apply_colors(t_map *map)
{
	int x;
	int y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->has_any_color)
			{
				if (!map->map[y][x].has_color)
				{
					map->map[y][x].color.r = 255;
					map->map[y][x].color.g = 255;
					map->map[y][x].color.b = 255;
					map->map[y][x].color.a = 255;
				}
			}
			else
				map->map[y][x].color = color_based_on_height(map->map[y][x].z, map);
			x++;
		}
		y++;
	}
}
