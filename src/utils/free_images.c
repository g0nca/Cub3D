/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:01:31 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/19 10:02:37 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Libera recursos do sistema de inimigos
 */
void	free_enemy_system(t_game *g)
{
	int	i;

	i = 0;
	while (i < ENEMY_ASSETS)
	{
		if (g->enemy_sys.enemy_textures[i].img)
			mlx_destroy_image(g->mlx, g->enemy_sys.enemy_textures[i].img);
		i++;
	}
}

void	free_weapon_system(t_game *g)
{
	int	i;

	i = 0;
	while (i < WEAPON_FRAMES)
	{
		if (g->weapon.textures[i].img)
			mlx_destroy_image(g->mlx, g->weapon.textures[i].img);
		i++;
	}
}