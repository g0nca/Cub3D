/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:37:46 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 14:40:33 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	count_neighbor_walls(t_game *g, int x, int y);

static char	get_cell(t_game *g, int x, int y)
{
	if (y < 0 || x < 0 || !g->map.grid[y]
		|| x >= (int)ft_strlen(g->map.grid[y]))
		return ('1');
	return (g->map.grid[y][x]);
}

int	check_cross_pattern(t_game *g, int x, int y)
{
	char	up;
	char	down;
	char	left;
	char	right;

	if (!g->map.grid[y] || x >= (int)ft_strlen(g->map.grid[y]))
		return (0);
	if (g->map.grid[y][x] != '1')
		return (0);
	up = get_cell(g, x, y - 1);
	down = get_cell(g, x, y + 1);
	left = get_cell(g, x - 1, y);
	right = get_cell(g, x + 1, y);
	if (up == '0' && down == '0' && left == '1' && right == '1')
		return (1);
	if (left == '0' && right == '0' && up == '1' && down == '1')
		return (1);
	return (0);
}

int	compare_sprites(const void *a, const void *b)
{
	t_unified_sprite	*sa;
	t_unified_sprite	*sb;

	sa = (t_unified_sprite *)a;
	sb = (t_unified_sprite *)b;
	if (sa->distance > sb->distance)
		return (-1);
	if (sa->distance < sb->distance)
		return (1);
	return (0);
}

void	collect_enemy_sprites(t_game *g, t_unified_sprite *sprites, int *cnt)
{
	int	i;

	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			sprites[*cnt].type = SPRITE_ENEMY;
			sprites[*cnt].x = g->enemy_sys.enemies[i].x;
			sprites[*cnt].y = g->enemy_sys.enemies[i].y;
			sprites[*cnt].distance = sqrt(pow(sprites[*cnt].x - g->player.x, 2)
					+ pow(sprites[*cnt].y - g->player.y, 2));
			sprites[*cnt].index = i;
			(*cnt)++;
		}
		i++;
	}
}

void	collect_door_sprites(t_game *g, t_unified_sprite *sprites, int *cnt)
{
	int	i;

	i = 0;
	while (i < g->door_sys.door_count)
	{
		sprites[*cnt].type = SPRITE_DOOR;
		sprites[*cnt].x = g->door_sys.doors[i].x + 0.5;
		sprites[*cnt].y = g->door_sys.doors[i].y + 0.5;
		sprites[*cnt].distance = sqrt(pow(sprites[*cnt].x - g->player.x, 2)
				+ pow(sprites[*cnt].y - g->player.y, 2));
		sprites[*cnt].index = i;
		(*cnt)++;
		i++;
	}
}
