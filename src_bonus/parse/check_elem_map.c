/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:48:22 by marvin            #+#    #+#             */
/*   Updated: 2025/11/08 15:48:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

bool	verify_color_elements(t_map *map)
{
	char		**f_split;
	char		**c_split;
	t_parse_ctx	ctx;

	f_split = ft_split(map->floor_color, ',');
	c_split = ft_split(map->ceiling_color, ',');
	if (!f_split || !c_split)
	{
		free_split_array(f_split);
		free_split_array(c_split);
		return (false);
	}
	ctx.map = map;
	ctx.f_split = f_split;
	ctx.c_split = c_split;
	ctx.mode = 1;
	colors_check(f_split, &ctx);
	ctx.mode = 0;
	colors_check(c_split, &ctx);
	free_split_array(f_split);
	free_split_array(c_split);
	return (true);
}

void	check_texture(t_map *map, char *line, int type)
{
	struct stat	info;

	if (ft_strlen(line) <= 0)
	{
		print_texture(type);
		print_error_and_exit_free("Texture Not Found", 1, map);
	}
	if (ft_strcmp(&line[ft_strlen(line) - 4], ".xpm") != 0)
		print_error_and_exit_free("Invalid Extension \"Example.xpm\"", 1, map);
	if (stat(line, &info) == -1)
	{
		print_error_and_exit_free("Invalid Path", 1, map);
		return ;
	}
	if (S_ISDIR(info.st_mode))
	{
		print_error_and_exit_free("Is a Directory", 1, map);
	}
	if (access(line, F_OK) == -1)
		print_error_and_exit_free("Texture Not Found", 1, map);
	if (access(line, R_OK) == -1)
	{
		print_texture(type);
		print_error_and_exit_free("Permission denied", 1, map);
	}
}

bool	verify_texture_elements(t_map *map)
{
	check_texture(map, map->no_texture, NO);
	check_texture(map, map->so_texture, SO);
	check_texture(map, map->we_texture, WE);
	check_texture(map, map->ea_texture, EA);
	return (true);
}

bool	check_elements(t_map *map)
{
	if (verify_texture_elements(map) == false)
		return (false);
	if (verify_color_elements(map) == false)
		return (false);
	return (true);
}
