/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:45:04 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:48 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	set_rgb_color(t_map *map)
{
	map->floor_rgb[0] = -1;
	map->floor_rgb[1] = -1;
	map->floor_rgb[2] = -1;
	map->ceiling_rgb[0] = -1;
	map->ceiling_rgb[1] = -1;
	map->ceiling_rgb[2] = -1;
}

t_map	*init_map_struct(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	set_rgb_color(map);
	map->start_x = -1;
	map->start_y = -1;
	map->exit_flag = 0;
	map->start = 0;
	map->last_map_line = 0;
	map->end = 0;
	map->height = 0;
	map->width = 0;
	map->player_p = false;
	return (map);
}
