/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:28:44 by andrade           #+#    #+#             */
/*   Updated: 2025/11/20 10:34:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Carrega todas as texturas dos inimigos (5 tipos x 8 frames cada)
 */
void	load_enemy_textures(t_game *g)
{
	char	path[256];
	int		enemy_type;
	int		frame;
	int		loaded_count;

	loaded_count = 0;
	enemy_type = 0;
	while (enemy_type < ENEMY_TYPES)
	{
		frame = 0;
		while (frame < FRAMES_PER_ENEMY)
		{
			// Caminho: assets/enemies/enemy0/enemy0_0.xpm até enemy4/enemy4_7.xpm
			snprintf(path, sizeof(path), "assets/enemies/enemy%d/enemy%d_%d.xpm",
				enemy_type, enemy_type, frame);

			g->enemy_sys.enemy_textures[enemy_type][frame].img = mlx_xpm_file_to_image(
				g->mlx, path,
				&g->enemy_sys.enemy_textures[enemy_type][frame].width,
				&g->enemy_sys.enemy_textures[enemy_type][frame].height);

			if (!g->enemy_sys.enemy_textures[enemy_type][frame].img)
			{
				g->enemy_sys.enemy_textures[enemy_type][frame].addr = NULL;
				g->enemy_sys.enemy_textures[enemy_type][frame].bpp = 0;
				g->enemy_sys.enemy_textures[enemy_type][frame].line_len = 0;
				g->enemy_sys.enemy_textures[enemy_type][frame].endian = 0;
			}
			else
			{
				loaded_count++;
				g->enemy_sys.enemy_textures[enemy_type][frame].addr = mlx_get_data_addr(
					g->enemy_sys.enemy_textures[enemy_type][frame].img,
					&g->enemy_sys.enemy_textures[enemy_type][frame].bpp,
					&g->enemy_sys.enemy_textures[enemy_type][frame].line_len,
					&g->enemy_sys.enemy_textures[enemy_type][frame].endian);
			}
			frame++;
		}
		enemy_type++;
	}
}

/**
 * Conta o número de tiles '0' (chão) no mapa
 */
int	count_floor_tiles(t_game *g)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			if (g->map.grid[y][x] == '0')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/**
 * Determina quantos inimigos spawnar baseado no número de tiles
 */
int	get_enemy_count_by_tiles(int tile_count)
{
	if (tile_count < 5)
		return (0);
	else if (tile_count <= 15)
		return (1);
	else if (tile_count <= 30)
		return (2);
	else if (tile_count <= 50)
		return (3);
	else if (tile_count <= 75)
		return (4);
	else if (tile_count <= 100)
		return (5);
	else
		return (1 + tile_count / 20);
}

/**
 * Inicializa o sistema de inimigos
 */
void	init_enemy_system(t_game *g)
{
	int	i;
	int	j;

	srand(time(NULL));
	i = 0;
	while (i < MAX_ENEMIES)
	{
		g->enemy_sys.enemies[i].active = 0;
		g->enemy_sys.enemies[i].x = 0.0;
		g->enemy_sys.enemies[i].y = 0.0;
		g->enemy_sys.enemies[i].enemy_type = 0;
		g->enemy_sys.enemies[i].current_frame = 0;
		g->enemy_sys.enemies[i].last_frame_time = 0;
		j = 0;
		while (j < FRAMES_PER_ENEMY)
		{
			g->enemy_sys.enemies[i].frames[j].img = NULL;
			g->enemy_sys.enemies[i].frames[j].addr = NULL;
			j++;
		}
		i++;
	}
	g->enemy_sys.enemy_count = 0;
	g->enemy_sys.game_over = 0;
	load_enemy_textures(g);
	spawn_enemies(g);
}
