/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_map_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:45:43 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/17 10:52:10 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		is_map_line(char *line, t_map *map)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (map->player_p == false && (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			map->player_p = true;
		else if (map->player_p == true && (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			print_error_and_exit_FREE("Only SinglePlayer Game, NOT MULTIPLAYER", 1, map);
 		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int		check_map(t_map *map, int *i)
{
	if (map->grid[*i][0] == '\n')
		return (0);
	if (is_map_line(map->grid[*i], map))
	{
		if (map->start == 0)
		{
			map->start = *i;
			map->last_map_line = *i;
		}
		else
		{
			if (*i != map->last_map_line + 1)
				print_error_and_exit_FREE("Invalid Map", 1, map);
			map->last_map_line = *i;
		}
		map->end = *i;
	}
	else if (map->start != 0)
		print_error_and_exit_FREE("Invalid Map", 1, map);
	return (0);
}

int		check_info(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == 'N' && line[i + 1] == 'O')
			return (NO);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			return (SO);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			return (WE);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			return (EA);
		else if (line[i] == 'F')
			return (F);
		else if (line[i] == 'C')
			return (C);
		i++;
	}
	return (0);
}

void	save_texture_or_color2(t_map *map, char *value, int info_status)
{

	if (info_status == WE)
	{
		if (map->we_texture == NULL)
			map->we_texture = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info_status == EA)
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

t_map	*save_info_to_map_struct(t_map *map, char *line, int info_status)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (info_status == NO)
	{
		if (map->no_texture == NULL)
			map->no_texture = ft_strdup(&line[i]);
		else
			map->exit_flag = 1;
	}
	else if (info_status == SO)
	{
		if (map->so_texture == NULL)
			map->so_texture = ft_strdup(&line[i]);
		else
			map->exit_flag = 1;
	}
	save_texture_or_color2(map, &line[i], info_status);
	return (map);
}