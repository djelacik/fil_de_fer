/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:07 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/17 19:21:13 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(void)
{
	mlx_t	    *mlx;
    mlx_image_t *img;

	mlx = mlx_init(WIDTH, HEIGHT, "Grid Window", true);
	if (!mlx)
	{
		printf("Failed to initialize MLX\n");
		return (EXIT_FAILURE);
	}
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		printf("Failed to create image\n");
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	draw_grid(img);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, close_window, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
