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

bool    check_elements(t_map *map)
{
    int floor[3];
    int ceiling[3];
    char **floor_split;
    char **ceiling_split;
    int i;

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
    i = 0;
    while (i < 3)
    {
        floor[i] = ft_atoi(floor_split[i]);
        ceiling[i] = ft_atoi(ceiling_split[i]);
        if (floor[i] < 0 || floor[i] > 255 || ceiling[i] < 0 || ceiling[i] > 255)
            return (false);
        free(floor_split[i]);
        free(ceiling_split[i]);
        i++;
    }
    i = 0;
    while (i < 3)
    {
        printf("FLOOR[%d]: %d\n", i, floor[i]);
        printf("CEILING[%d]: %d\n", i, ceiling[i]);
        i++;
    }
    //printf("FLOOR:%s\n", map->floor_color);
    return (true);
}
