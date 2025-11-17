/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:43:22 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/17 10:48:04 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		map_height(t_map *map)
{
	int i;

	i = 0;
	while (map->grid[i])
		i++;
	return (i);
}

void	trim_newline_center(t_map *map, int flag)
{
	int i;

	i = 0;
	if (flag == 0)
	{
		trim_newline(map->no_texture);
		trim_newline(map->so_texture);
		trim_newline(map->we_texture);
		trim_newline(map->ea_texture);
		trim_newline(map->floor_color);
		trim_newline(map->ceiling_color);
	}
	else if (flag == 1)
	{
		while (map->grid[i])
		{
			trim_newline(map->grid[i]);
			i++;
		}
	}
}

void	trim_newline(char *str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}

int		ft_line_count(char **av, t_map *map)
{
	int		line_count;
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (-1);
	}
	line_count = 1;
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		print_error_and_exit_FREE("Empty File", 1, map);
	}
	free(line);
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}