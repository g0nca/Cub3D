/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_map_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:45:43 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:03 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_map_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (map->player_p == false && (line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			map->player_p = true;
		else if (map->player_p == true && (line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			print_error_and_exit_free(
				"Only SinglePlayer Game, NOT MULTIPLAYER", 1, map);
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_map(t_map *map, int *i)
{
	if (map->grid[*i][0] == '\n' || map->grid[*i] == NULL)
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
				print_error_and_exit_free("Invalid Map", 1, map);
			map->last_map_line = *i;
		}
		map->end = *i;
	}
	else if (map->start != 0)
		print_error_and_exit_free("Invalid Map", 1, map);
	return (0);
}

int	check_info(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] == 'N' && line[i + 1] == 'O')
			return (NO);
		if (line[i] == 'S' && line[i + 1] == 'O')
			return (SO);
		if (line[i] == 'W' && line[i + 1] == 'E')
			return (WE);
		if (line[i] == 'E' && line[i + 1] == 'A')
			return (EA);
		if (line[i] == 'F')
			return (F);
		if (line[i] == 'C')
			return (C);
		i++;
	}
	return (0);
}

t_map	*save_info_to_map_struct(t_map *map, char *line, int info_status)
{
	int	i;

	i = delete_spaces(line, info_status);
	save_texture_or_color1(map, &line[i], info_status);
	save_texture_or_color2(map, &line[i], info_status);
	return (map);
}
