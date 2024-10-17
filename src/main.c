/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:02:07 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/16 12:29:33 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	start_process(mlx_t **mlx, char *filename, t_map **map)
{
	*map = initialize_map((*mlx), filename);
	if (!*map)
	{
		return (error_exit((*mlx), (*map), ERROR_MSG));
	}
	*mlx = initalize_mlx(filename);
	if (!*mlx)
	{
		return (error_exit((*mlx), (*map), ERROR_MSG));
	}
	(*map)->img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (!(*map)->img)
	{
		return (error_exit((*mlx), (*map), ERROR_MSG));
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
	mlx_terminate(mlx);
	return (error_exit(mlx, map, EXIT_MSG));
}
