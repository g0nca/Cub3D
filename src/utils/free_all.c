/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 15:51:32 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_images(t_game *g)
{
	if (g->textures.north.img)
		mlx_destroy_image(g->mlx, g->textures.north.img);
	if (g->textures.south.img)
		mlx_destroy_image(g->mlx, g->textures.south.img);
	if (g->textures.west.img)
		mlx_destroy_image(g->mlx, g->textures.west.img);
	if (g->textures.east.img)
		mlx_destroy_image(g->mlx, g->textures.east.img);
}

void	free_split_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_all(t_cub *cub)
{
	int	i;

	i = 0;
	free(cub->map->no_texture);
	free(cub->map->so_texture);
	free(cub->map->we_texture);
	free(cub->map->ea_texture);
	free(cub->map->floor_color);
	free(cub->map->ceiling_color);
	while (cub->map->grid[i])
	{
		free(cub->map->grid[i]);
		cub->map->grid[i] = NULL;
		i++;
	}
	free(cub->map->grid);
	free(cub->map);
}

void	ft_free_map(char **map)
{
	int	i;

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
