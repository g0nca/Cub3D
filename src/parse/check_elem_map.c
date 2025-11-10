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

static void save_color_values(char *color_str, t_map *map, int floor_or_ceiling, int index)
{
    int value;
    
    value = ft_atoi(color_str);
    if (value < 0 || value > 255)
        print_error_and_exit_without_free("The numbers exceed the valid range", 1, map);
    
    if (floor_or_ceiling == 1)
        map->floor_rgb[index] = value;
    else if (floor_or_ceiling == 0)
        map->ceiling_rgb[index] = value;
}
static void		check_only_three_numbers(t_map *map, int i)
{
    if (i != 3)
        print_error_and_exit_without_free("Only 3 numbers are accepted", 1, map);
}

static void colors_check(char **colors, t_map *map, int floor_or_ceiling)
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
                print_error_and_exit_without_free("Invalid decimal numbers", 1, map);
            if (colors[i][j] == ' ' && num_exist == false && colors[i][j + 1] == '\0')
                print_error_and_exit_without_free("Missing numbers", 1, map);
            if (colors[i][j] >= '0' && colors[i][j] <= '9')
                num_exist = true;
			j++;
        }
        save_color_values(colors[i], map, floor_or_ceiling, i);
        free(colors[i]);
        i++;
    }
	check_only_three_numbers(map, i);
    free(colors);
}

bool    check_elements(t_map *map)
{
    char **floor_split;
    char **ceiling_split;
    
    if (access(map->no_texture, F_OK) == -1)
        return (false);
    if (access(map->so_texture, F_OK) == -1)
        return (false);
    if (access(map->we_texture, F_OK) == -1)
        return (false);
    if (access(map->ea_texture, F_OK) == -1)
        return (false);
    floor_split = ft_split(map->floor_color, ',');
    ceiling_split = ft_split(map->ceiling_color, ',');
    if (!floor_split || !ceiling_split)
        return (false);
    colors_check(floor_split, map, 1);
    colors_check(ceiling_split, map, 0);
	
    return (true);
}
