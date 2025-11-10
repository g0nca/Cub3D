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

static void safe_exit_with_splits(char *msg, t_map *map, 
                                   char **floor_split, char **ceiling_split)
{
    free_split_array(floor_split);
    free_split_array(ceiling_split);
    print_error_and_exit_without_free(msg, 1, map);
}

static void save_color_values(char *color_str, t_map *map, int floor_or_ceiling, 
                               int index, char **floor_split, char **ceiling_split)
{
    int value;
    
    value = ft_atoi(color_str);
    if (value < 0 || value > 255)
        safe_exit_with_splits("The numbers exceed the valid range", 
                              map, floor_split, ceiling_split);
    if (floor_or_ceiling == 1)
        map->floor_rgb[index] = value;
    else if (floor_or_ceiling == 0)
        map->ceiling_rgb[index] = value;
}

static void colors_check(char **colors, t_map *map, int floor_or_ceiling,
                         char **floor_split, char **ceiling_split)
{
    int     i;
    int     j;
    bool    num_exist;
    
    i = 0;
    while (colors[i])
    {
        j = 0;
        num_exist = false;
        while (colors[i][j])
        {
            if (colors[i][j] == '.')
                safe_exit_with_splits("Invalid decimal numbers", 
                                      map, floor_split, ceiling_split);
            if (colors[i][j] == ' ' && num_exist == false 
                && colors[i][j + 1] == '\0')
                safe_exit_with_splits("Missing numbers", 
                                      map, floor_split, ceiling_split);
            if (colors[i][j] >= '0' && colors[i][j] <= '9')
                num_exist = true;
            j++;
        }
        save_color_values(colors[i], map, floor_or_ceiling, i, 
                         floor_split, ceiling_split);
        i++;
    }
    if (i != 3)
        safe_exit_with_splits("Only 3 numbers are accepted", 
                              map, floor_split, ceiling_split);
}
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
        print_error_and_exit_without_free("Invalid file extension \"Example.xpm\"", 1, NULL);
	if (access(line, F_OK) == -1)
		print_error_and_exit_FREE("Texture Not Found", 1, map);
	if (access(line, R_OK) == -1)
		print_error_and_exit_FREE("Permission denied", 1, map);
    if (stat(line, &info) == -1)
    {
        perror("stat");
        return ;
    }
    if (S_ISDIR(info.st_mode))
        print_error_and_exit_without_free("Is a Directory", 1, map);
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
