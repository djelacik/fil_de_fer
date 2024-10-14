/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:07 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/14 16:38:09 by djelacik         ###   ########.fr       */
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


static void	handle_movement(mlx_t *mlx, t_map *map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		map->y_offset -= 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		map->y_offset += 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		map->x_offset -= 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		map->x_offset += 0.1;
}

static void	handle_scaling(mlx_t *mlx, t_map *map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
	{
		//map->z_multiplier *= 1.01;
		//multiply_z(map, 1.01);
		map->z_scale *= 0.99;
		find_max_min_z(map);
	map->max_z /= map->z_scale;
	map->min_z /= map->z_scale;

		
	}
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
	{
		// map->z_multiplier *= 0.99;
		// if (map->z_multiplier < 0.01)
		// 	map->z_multiplier = 0.1;
		//multiply_z(map, 0.99);
			map->z_scale *= 1.01;

		find_max_min_z(map);
			map->max_z /= map->z_scale;
	map->min_z /= map->z_scale;

	}
}

static void	redraw(mlx_t *mlx, t_map *map)
{
	if (map->img)
	{
		mlx_delete_image(mlx, map->img);
		map->img = NULL;
	}
	map->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!map->img)
	{
		return ;
	}
	draw_map(map->img, map);
	mlx_image_to_window(mlx, map->img, 0, 0);
}

static void	loop_hook(void *param)
{
	t_context	*context;
	mlx_t		*mlx;
	t_map		*map;
	
	context = (t_context *)param;
	mlx = context->mlx;
	map = context->map;
	handle_movement(mlx, map);
	handle_scaling(mlx, map);
	redraw(mlx, map);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_map		*map;
	t_context	context;
	
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
	mlx = initalize_mlx(argv[1]);
	if (!mlx)
	{
		return (EXIT_FAILURE);
	}
	map->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!map->img)
	{
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	draw_map(map->img, map);
	mlx_image_to_window(mlx, map->img, 0, 0);
	context.map = map;
	context.mlx = mlx;
	mlx_loop_hook(mlx, loop_hook, &context);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
