/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_texture_or_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:58:08 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:00 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	save_texture_or_color1(t_map *map, char *value, int info)
{
	if (info == NO)
	{
		if (map->no_texture == NULL)
			map->no_texture = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info == SO)
	{
		if (map->so_texture == NULL)
			map->so_texture = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info == WE)
	{
		if (map->we_texture == NULL)
			map->we_texture = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
}

void	save_texture_or_color2(t_map *map, char *value, int info_status)
{
	if (info_status == EA)
	{
		if (map->ea_texture == NULL)
			map->ea_texture = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info_status == F)
	{
		if (map->floor_color == NULL)
			map->floor_color = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info_status == C)
	{
		if (map->ceiling_color == NULL)
			map->ceiling_color = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
}
