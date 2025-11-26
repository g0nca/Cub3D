/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:43:22 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:07 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	map_height(t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i])
		i++;
	return (i);
}

int	delete_spaces(char *line, int info_status)
{
	int	i;

	i = 0;
	while (line[i] && info_status >= 1 && info_status <= 6)
	{
		if ((info_status >= 1 && info_status <= 4)
			&& (line[i] == '.' && line[i + 1] == '/'))
			return (i);
		if (info_status == 5 || info_status == 6)
		{
			while (line[i] && line[i] != ' ')
				i++;
			while (line[i] && line[i] == ' ')
				i++;
			return (i);
		}
		i++;
	}
	return (i);
}

void	trim_newline_center(t_map *map, int flag)
{
	int	i;

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
	int	i;

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

int	ft_line_count(char **av, t_map *map)
{
	int		line_count;
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	line_count = 1;
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		print_error_and_exit_free("Empty File", 1, map);
	}
	free(line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}
