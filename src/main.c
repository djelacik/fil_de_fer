/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:07 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/23 10:55:32 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	start_process(mlx_t **mlx, char *filename, t_map **map)
{
	*map = initialize_map(filename);
	if (!*map)
	{
		return (error_exit((*map), ERROR_MSG));
	}
	*mlx = initalize_mlx(filename);
	if (!*mlx)
	{
		return (error_exit((*map), ERROR_MSG));
	}
	(*map)->img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (!(*map)->img)
	{
		return (error_exit((*map), ERROR_MSG));
	}
	draw_map((*map)->img, *map);
	mlx_image_to_window(*mlx, (*map)->img, 0, 0);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_map		*map;
	t_context	context;

	mlx = NULL;
	if (argc != 2)
	{
		ft_putstr_fd(ARGC_ERR, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!check_name(argv[1]))
	{
		ft_putstr_fd(FORMAT_ERR, STDERR_FILENO);
		return (1);
	}
	if (start_process(&mlx, argv[1], &map))
		return (EXIT_FAILURE);
	context.map = map;
	context.mlx = mlx;
	mlx_loop_hook(mlx, loop_hook, &context);
	mlx_loop(mlx);
	mlx_delete_image(mlx, map->img);
	mlx_terminate(mlx);
	return (error_exit(map, EXIT_MSG));
}
