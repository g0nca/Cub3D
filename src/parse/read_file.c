/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:20:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 15:36:33 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_map	*init_map_struct(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	return (map);
}

static int		ft_line_count(char **av, t_map *map)
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
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

static int	copy_to_struct(char **av, t_map *map)
{
	int fd;
	int i;
	char *line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free(map->map);
		free(map);
		return (-1);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->map[i] = line;
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		i++;
	}
	map->map[i] = NULL;
	map->height = i;
	close(fd);	
	return (0);
}

t_map	*read_file_parse(char **av)
{
	t_map	*map;
	int		line_count;
	

	map = init_map_struct();
	line_count = ft_line_count(av, map);
	if (line_count <= 0)
	{
		free(map);
		return (NULL);
	}
	map->map = malloc(sizeof(char *) * (line_count + 1));
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	if (copy_to_struct(av, map) == -1)
		return (NULL);
	return (map);
}
