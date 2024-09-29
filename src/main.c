/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:07 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/29 15:55:23 by djelacik         ###   ########.fr       */
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
//                 printf("%d, ", map->map[y][x]);
//             else
//                 printf("%d", map->map[y][x]);  // Viimeinen arvo rivillä ilman pilkkua
//             x++;
//         }
//         printf("\n");  // Uusi rivi kartassa
//         y++;
//     }
// }

int	main(int argc, char **argv)
{
	mlx_t	    *mlx;
    mlx_image_t *img;
	t_map		*map;
	
	if (argc != 2)
    {
        printf("Usage: ./fdf <filename>\n");
        return (1);
    }	
	map = save_map(argv[1]);
	if (!map)
	{
		printf("Error saving the map\n");
		return (1);
	}
	find_max_min_z(map);
	save_map_size(map);
	map_scale(map);
	
	mlx = mlx_init(WIDTH, HEIGHT, "Test_window", true);
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
	//printf("Map width: %d, height: %d\n", map->width, map->height);
	//print_map(map);
	draw_map(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, close_window, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
