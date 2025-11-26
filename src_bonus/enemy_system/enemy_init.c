/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:28:44 by andrade           #+#    #+#             */
/*   Updated: 2025/11/26 14:29:59 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/**
 * Conta o número de tiles '0' (chão) no mapa
 */
int	count_floor_tiles(t_game *g)
{
	int	count;
	int	y;
	int	x;

	if (!g || !g->map.grid)
		return (0);
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

/*
    Compare sprites by nearest distance first
*/
int	compare_sprites_nearest_first(const void *a, const void *b)
{
	double	distance_a;
	double	distance_b;

	distance_a = ((t_sprite_data *)a)->distance;
	distance_b = ((t_sprite_data *)b)->distance;
	if (distance_a < distance_b)
		return (-1);
	else if (distance_a > distance_b)
		return (1);
	else
		return (0);
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

static void	init_enemy_system_var(t_game *g, int i)
{
	g->enemy_sys.enemies[i].active = 0;
	g->enemy_sys.enemies[i].x = 0.0;
	g->enemy_sys.enemies[i].y = 0.0;
	g->enemy_sys.enemies[i].enemy_type = 0;
	g->enemy_sys.enemies[i].current_frame = 0;
	g->enemy_sys.enemies[i].last_frame_time = 0;
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
		init_enemy_system_var(g, i);
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
