/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/07 15:55:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_all(t_cub *cub)
{
	int		i;

	i = 0;

	free(cub->map->no_texture);
    free(cub->map->so_texture);
    free(cub->map->we_texture);
    free(cub->map->ea_texture);
    free(cub->map->floor_color);
    free(cub->map->ceiling_color);
	while (cub->map->map[i])
	{
		free(cub->map->map[i]);
		cub->map->map[i] = NULL;
		i++;
	}
	free(cub->map->map);
	free(cub->map);
}

void	ft_free_map(char **map)
{
	int     i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}