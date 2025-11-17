/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:55:26 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/17 10:57:20 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**copy_map_grid(t_map *map)
{
	char	**map_copy;
	int		i;

	if (!map->grid)
		return (NULL);
	map_copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (map->grid[i])
	{
		map_copy[i] = ft_strdup(map->grid[i]);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

int		flood_fill(char **map_copy, int x, int y, int width, int height)
{
	char	c;
	int		line_len;

	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0);
	line_len = ft_strlen(map_copy[y]);
	if (x < 0 || x >= line_len)
		return (0);
	c = map_copy[y][x];
	if (c == '1' || c == 'V')
		return (1);
	if (c == ' ' || c == '\0' || c == '\n')
	{
		if ((c == ' ' || c == '\0') && (y == 0 || y == height -1 || x == 0 || x == width -1))
			return (0);
	}
	map_copy[y][x] = 'V';
	if (!flood_fill(map_copy, x, y - 1, width, height))
		return (0);
	if (!flood_fill(map_copy, x, y + 1, width, height))
		return (0);
	if (!flood_fill(map_copy, x - 1, y, width, height))
		return (0);
	if (!flood_fill(map_copy, x + 1, y, width, height))
		return (0);
	return (1);
}

int		find_player_position_parse(t_map *map, int *start_x, int *start_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' || map->grid[y][x] == 'W' || map->grid[y][x] == 'E')
			{
				*start_x = x;
				*start_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}