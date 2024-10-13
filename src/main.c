/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:07 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/13 20:55:22 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// static void print_map(t_map *map)
// {
//     int x;
//     int y;

//     y = 0;
//     while (y < map->height)
//     {
//         x = 0;
//         while (x < map->width)
//         {
//             // Tulosta z-arvo ja lisää pilkku paitsi viimeisen arvon jälkeen
//             if (x < map->width - 1)
//                 printf("%.0f, ", map->map[y][x].z);
//             else
//                 printf("%.0f", map->map[y][x].z);  // Viimeinen arvo rivillä ilman pilkkua
//             x++;
//         }
//         printf("\n");  // Uusi rivi kartassa
//         y++;
//     }
// }

static t_map	*initialize_map(char *filename)
{
	t_map	*map;

	map = save_map(filename);
	if (!map)
	{
		printf("Error saving the map\n");
		return (NULL);
	}
	find_max_min_z(map);
	save_map_size(map);
	map_scale(map);
	apply_colors(map);	
	return (map);
}

static mlx_t	*initalize_mlx(mlx_image_t **img, const char *filename)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, filename, true);
	if (!mlx)
	{
		printf("Failed to initialize MLX\n");
		return (NULL);
	}
	*img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		printf("Failed to create image\n");
		mlx_terminate(mlx);
		return (NULL);
	}
	return (mlx);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
    mlx_image_t *img;
	t_map		*map;
	
	if (argc != 2)
    {
        printf("Usage: ./fdf <filename>\n");
        return (1);
    }	
	map = initialize_map(argv[1]);
	if (!map)
	{
		return (EXIT_FAILURE);
	}
	mlx = initalize_mlx(&img, argv[1]);
	draw_map(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, close_window, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
