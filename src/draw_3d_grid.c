/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:45:24 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/20 01:57:44 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#define Z_SCALE 10

static int get_z_value(int x, int y)
{
    // Esimerkki sini-cos funktiosta. Voit käyttää omaa funktiotasi tai dataasi
    int z = (int)(Z_SCALE * sin((float)x / 100) * cos((float)y / 100));
    printf("Calculating z for x = %d, y = %d: z = %d\n", x, y, z);
    return z;
}

static void	apply_isometric(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;

	// Isometrinen projektio
	*x = (previous_x - previous_y) * cos(0.6); // 30 astetta radiaaneina
	*y = (previous_x + previous_y) * sin(0.6) - z;

	// Skaalataan ja siirretään ruudukko keskelle
	*x = *x / 4 * 2 + WIDTH / 2;  // Skaalaus ja offset x:lle
	*y = *y / 4 * 2 + HEIGHT / 4; // Skaalaus ja offset y:lle
}

void	draw_grid(mlx_image_t *img)
{
	t_points	points;
	int			x;
	int			y;
	int			z0, z1;

	// Piirretään vaakasuorat viivat
	y = 0;
	while (y <= HEIGHT)
	{
		x = 0;
		while (x + GRID_SIZE <= WIDTH)
		{
			z0 = get_z_value(x, y);
			z1 = get_z_value(x + GRID_SIZE, y);

			// Alkuperäiset pisteet
			points.x0 = x;
			points.y0 = y;
			points.x1 = x + GRID_SIZE;
			points.y1 = y;

			// Muutetaan isometriseksi
			apply_isometric(&points.x0, &points.y0, z0);
			apply_isometric(&points.x1, &points.y1, z1);

			draw_line(img, points, 0xFF0000FF); // Piirretään viiva
			x += GRID_SIZE;
		}
		y += GRID_SIZE;
	}

	// Piirretään pystysuorat viivat
	x = 0;
	while (x <= WIDTH)
	{
		y = 0;
		while (y + GRID_SIZE <= HEIGHT)
		{
			z0 = get_z_value(x, y);
			z1 = get_z_value(x, y + GRID_SIZE);

			// Alkuperäiset pisteet
			points.x0 = x;
			points.y0 = y;
			points.x1 = x;
			points.y1 = y + GRID_SIZE;

			// Muutetaan isometriseksi
			apply_isometric(&points.x0, &points.y0, z0);
			apply_isometric(&points.x1, &points.y1, z1);

			draw_line(img, points, 0xFF0000FF); // Piirretään viiva
			y += GRID_SIZE;
		}
		x += GRID_SIZE;
	}
}
