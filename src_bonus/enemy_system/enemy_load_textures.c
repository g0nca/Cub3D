/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_load_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:28:37 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:02 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	load_enemy_texture_info(t_game *g, char path[256],
	int frame, int enemy_type)
{
	g->enemy_sys.enemy_textures[enemy_type][frame].img = mlx_xpm_file_to_image(
			g->mlx, path,
			&g->enemy_sys.enemy_textures[enemy_type][frame].width,
			&g->enemy_sys.enemy_textures[enemy_type][frame].height);
}

static void	load_enemy_texture_info2(t_game *g, int frame, int enemy_type)
{
	g->enemy_sys.enemy_textures[enemy_type][frame].addr = NULL;
	g->enemy_sys.enemy_textures[enemy_type][frame].bpp = 0;
	g->enemy_sys.enemy_textures[enemy_type][frame].line_len = 0;
	g->enemy_sys.enemy_textures[enemy_type][frame].endian = 0;
}

static void	load_enemy_texture_info3(t_game *g, int frame, int enemy_type)
{
	g->enemy_sys.enemy_textures[enemy_type][frame].addr = mlx_get_data_addr(
			g->enemy_sys.enemy_textures[enemy_type][frame].img,
			&g->enemy_sys.enemy_textures[enemy_type][frame].bpp,
			&g->enemy_sys.enemy_textures[enemy_type][frame].line_len,
			&g->enemy_sys.enemy_textures[enemy_type][frame].endian);
}

static void	iterates_all_frames(t_game *g, int frame, int enemy_type)
{
	int		loaded_count;
	char	path[256];

	loaded_count = 0;
	while (frame < FRAMES_PER_ENEMY)
	{
		snprintf(path, sizeof(path), "assets/enemies/enemy%d/enemy%d_%d.xpm",
			enemy_type, enemy_type, frame);
		load_enemy_texture_info(g, path, frame, enemy_type);
		if (!g->enemy_sys.enemy_textures[enemy_type][frame].img)
			load_enemy_texture_info2(g, frame, enemy_type);
		else
		{
			loaded_count++;
			load_enemy_texture_info3(g, frame, enemy_type);
		}
		frame++;
	}
}

/**
 * Carrega todas as texturas dos inimigos (5 tipos x 8 frames cada)
 */
void	load_enemy_textures(t_game *g)
{
	int		enemy_type;
	int		frame;

	enemy_type = 0;
	while (enemy_type < ENEMY_TYPES)
	{
		frame = 0;
		iterates_all_frames(g, frame, enemy_type);
		enemy_type++;
	}
}
