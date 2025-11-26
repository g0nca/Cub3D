/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:37:46 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 12:20:15 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_neighbor_walls(t_game *g, int x, int y);

/* Verifica padrão: O tile deve ser '1' e ter exatamente 2 paredes vizinhas */
int	check_cross_pattern(t_game *g, int x, int y)
{
	if (!g->map.grid[y] || x >= (int)ft_strlen(g->map.grid[y]))
		return (0);
	if (g->map.grid[y][x] != '1')
		return (0);
	return (count_neighbor_walls(g, x, y) == 2);
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

/* Desenhar pixel (igual ao original) */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
