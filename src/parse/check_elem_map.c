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
    if (access(map->no_texture, F_OK) == -1)
        return (false);
    /*if (access(map->so_texture, F_OK) == -1)
        return (false);
    if (access(map->we_texture, F_OK) == -1)
        return (false);
    if (access(map->ea_texture, F_OK) == -1)
        return (false);*/
    return (true);
}