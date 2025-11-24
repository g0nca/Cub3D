/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_only_map_lines.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:52:57 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 15:31:47 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_map	*save_only_map_lines(t_map *map)
{
	int		i;
	int		j;
	char	**only_map;

	if (map->start == 0 && map->end == 0)
		return (map);
	only_map = malloc(sizeof(char *) * (map->end - map->start + 2));
	if (!only_map)
		return (NULL);
	i = map->start;
	j = 0;
	while (i <= map->end)
	{
		only_map[j] = ft_strdup(map->grid[i]);
		if (ft_strlen(only_map[j]) - 1 == '\n')
			only_map[j][ft_strlen(only_map[j]) - 1] = '\0';
		j++;
		i++;
	}
	only_map[j] = NULL;
	i = 0;
	ft_free_map(map->grid);
	map->grid = only_map;
	return (map);
}
