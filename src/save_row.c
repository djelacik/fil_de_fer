/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_row.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:29:24 by djelacik          #+#    #+#             */
/*   Updated: 2024/10/08 16:31:34 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	parse_number(char *line, int *i)
{
	int		start;
	char	*str;
	int		number;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != ',')
		(*i)++;
	str = ft_substr(line, start, *i - start);
	number = ft_atoi(str);
	free(str);
	return (number);
}

static void	parse_color(char *line, int *i, t_point *point, t_map *map)
{
	int		start;
	char	*str;

	if (line[*i] == ',')
	{
		(*i)++;
		start = *i;
		while (line[*i] && line[*i] != ' ')
			(*i)++;
		str = ft_substr(line, start, *i - start);
		point->color = hex_to_color(str);
		point->has_color = 1;
		map->has_any_color = 1;
		free(str);
	}
	else
		point->has_color = 0;
}

int	fill_row(t_point *row, char *line, t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		row[j].z = parse_number(line, &i);
		parse_color(line, &i, &row[j], map);
		j++;
	}
	return (1);
}
