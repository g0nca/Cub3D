/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:56:14 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:41 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/**
 * Libera recursos do sistema de inimigos
 */
void	free_enemy_system(t_game *g)
{
	int	enemy_type;
	int	frame;

	enemy_type = 0;
	while (enemy_type < ENEMY_TYPES)
	{
		frame = 0;
		while (frame < FRAMES_PER_ENEMY)
		{
			if (g->enemy_sys.enemy_textures[enemy_type][frame].img)
				mlx_destroy_image(g->mlx,
					g->enemy_sys.enemy_textures[enemy_type][frame].img);
			frame++;
		}
		enemy_type++;
	}
}

void	free_weapon_texture_system(t_game *g)
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
