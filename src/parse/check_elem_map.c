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

#include "../../include/cub3d.h"

bool	verify_color_elements(t_map *map)
{
	char	**floor_split;
	char	**ceiling_split;

	floor_split = ft_split(map->floor_color, ',');
    ceiling_split = ft_split(map->ceiling_color, ',');
    if (!floor_split || !ceiling_split)
    {
        free_split_array(floor_split);
        free_split_array(ceiling_split);
        return (false);
    }
    colors_check(floor_split, map, 1, floor_split, ceiling_split);
    colors_check(ceiling_split, map, 0, floor_split, ceiling_split);
    free_split_array(floor_split);
    free_split_array(ceiling_split);
	return (true);
}
void	check_texture(t_map *map, char *line)
{
	struct stat info;
	int len;

	len = ft_strlen(line);
	if (ft_strcmp(&line[len - 4], ".xpm") != 0)
        print_error_and_exit_FREE("Invalid file extension \"Example.xpm\"", 1, map);
    if (stat(line, &info) == -1)
    {
        print_error_and_exit_FREE("Invalid Path", 1, map);
        return ;
    }

    if (S_ISDIR(info.st_mode))
	{
        print_error_and_exit_FREE("Is a Directory", 1, map);
	}
	
	if (access(line, F_OK) == -1)
		print_error_and_exit_FREE("Texture Not Found", 1, map);
	if (access(line, R_OK) == -1)
		print_error_and_exit_FREE("Permission denied", 1, map);
	
}
bool	verify_texture_elements(t_map *map)
{
	check_texture(map, map->no_texture);
	check_texture(map, map->so_texture);
	check_texture(map, map->we_texture);
	check_texture(map, map->ea_texture);
	return (true);
}
bool    check_elements(t_map *map)
{
	if (verify_texture_elements(map) == false)
		return (false);
	if (verify_color_elements(map) == false)
		return (false);
    
    return (true);
}
