/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:45:24 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/17 21:04:10 by djelacik         ###   ########.fr       */
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

void	draw_grid(mlx_image_t *img)
{
	t_points	points;
	int			x;
	int			y;
    int         z0, z1; // Z-arvot (korkeudet)

    // Piirretään vaakasuorat viivat
	y = 0;
	int i = 0;
	while(i++ < 5)
	{
        // Lasketaan korkeudet z-arvoina
        z0 = get_z_value(0, y);
        z1 = get_z_value(WIDTH, y);

        printf("Drawing horizontal line at y = %d with z0 = %d, z1 = %d\n", y, z0, z1);

		points.x0 = 0;
		points.y0 = y - z0;  // Vähennetään z-arvo y-koordinaatista
		points.x1 = WIDTH;
		points.y1 = y - z1;  // Vähennetään z-arvo y-koordinaatista

        printf("Line coordinates: x0 = %d, y0 = %d, x1 = %d, y1 = %d\n", points.x0, points.y0, points.x1, points.y1);
		draw_line(img, points, 0xFF0000FF); // Piirretään vaakasuora viiva
		y += GRID_SIZE;
	}

    // Piirretään pystysuorat viivat
	x = 0;
	i = 0;
	while (i++ < 5)
	{
        // Lasketaan korkeudet z-arvoina
        z0 = get_z_value(x, 0);
        z1 = get_z_value(x, HEIGHT);

        printf("Drawing vertical line at x = %d with z0 = %d, z1 = %d\n", x, z0, z1);

		points.x0 = x;
		points.y0 = 0 - z0;  // Vähennetään z-arvo y-koordinaatista
		points.x1 = x;
		points.y1 = HEIGHT - z1;  // Vähennetään z-arvo y-koordinaatista

        printf("Line coordinates: x0 = %d, y0 = %d, x1 = %d, y1 = %d\n", points.x0, points.y0, points.x1, points.y1);
		draw_line(img, points, 0xFF0000FF); // Piirretään pystysuora viiva
		x += GRID_SIZE;
	}
}
