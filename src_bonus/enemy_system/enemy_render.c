/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:39:39 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:08 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/* enemy_render_utils.c */
void	render_sprite_projection(t_game *g, t_enemy *enemy, t_img *tex);

static int	compare_sprites(const void *a, const void *b)
{
	t_sprite_data	*sa;
	t_sprite_data	*sb;

	sa = (t_sprite_data *)a;
	sb = (t_sprite_data *)b;
	if (sa->distance > sb->distance)
		return (-1);
	if (sa->distance < sb->distance)
		return (1);
	return (0);
}

static void	render_single_enemy(t_game *g, t_enemy *enemy)
{
	t_img	*current_texture;

	current_texture = &enemy->frames[enemy->current_frame];
	if (!current_texture->img || !current_texture->addr)
		return ;
	render_sprite_projection(g, enemy, current_texture);
}

static int	fill_sprite_array(t_game *g, t_sprite_data *sprites)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			sprites[count].index = i;
			sprites[count].x = g->enemy_sys.enemies[i].x;
			sprites[count].y = g->enemy_sys.enemies[i].y;
			sprites[count].distance = sqrt(
					pow(g->player.x - sprites[count].x, 2)
					+ pow(g->player.y - sprites[count].y, 2));
			count++;
		}
		i++;
	}
	return (count);
}

void	render_enemies(t_game *g)
{
	t_sprite_data	sprites[MAX_ENEMIES];
	int				sprite_count;
	int				i;

	if (g->enemy_sys.game_over)
		return ;
	sprite_count = fill_sprite_array(g, sprites);
	if (sprite_count > 0)
		qsort(sprites, sprite_count, sizeof(t_sprite_data), compare_sprites);
	i = 0;
	while (i < sprite_count)
	{
		render_single_enemy(g, &g->enemy_sys.enemies[sprites[i].index]);
		i++;
	}
}
