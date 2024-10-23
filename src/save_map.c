/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 02:04:18 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/18 15:24:06 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	get_width(char *line)
{
	int		width;
	int		i;

	width = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
		{
			width++;
			while (line[i] && line[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (width);
}

static void	save_height_and_width(t_map *map, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	map->height = 0;
	line = get_next_line(fd);
	map->width = get_width(line);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	allocate_map(t_map *map)
{
	int	i;

	map->map = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->map)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->map[i] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->map[i])
		{
			free_map_memory(map);
			return (0);
		}
		i++;
	}
	return (1);
}

t_map	*save_map(const char *filename)
{
	int		fd;
	int		i;
	char	*line;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ft_bzero(map, sizeof(t_map));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	save_height_and_width(map, filename);
	if (!allocate_map(map))
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		fill_row(map->map[i++], line, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}
