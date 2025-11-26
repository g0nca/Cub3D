/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemy_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:40:59 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 15:15:40 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*
    Prepare sprite data for hit detection
    Calculate distance from player to each enemy
*/
static void	prepare_sprite_data(t_game *g, t_sprite_data *sprites,
	int *sprite_count)
{
	int	i;

	*sprite_count = 0;
	i = 0;
	while (i < MAX_ENEMIES)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			sprites[*sprite_count].index = i;
			sprites[*sprite_count].x = g->enemy_sys.enemies[i].x;
			sprites[*sprite_count].y = g->enemy_sys.enemies[i].y;
			sprites[*sprite_count].distance = sqrt(
					pow(g->player.x - sprites[*sprite_count].x, 2)
					+ pow(g->player.y - sprites[*sprite_count].y, 2)
					);
			(*sprite_count)++;
		}
		i++;
	}
}

/*
 * Recebe um array 'trans' de tamanho 2 onde guarda os resultados.
 * trans[0] = transform_x
 * trans[1] = transform_y
 */
static void	calculate_transform(t_game *g, double sprite_x, double sprite_y,
			double *trans)
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	inv_det;

	dir_x = cos(g->player.angle);
	dir_y = sin(g->player.angle);
	plane_x = -dir_y * 0.66;
	plane_y = dir_x * 0.66;
	inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
	trans[0] = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
	trans[1] = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);
}

/*
    Check if the center x coordinate of the screen
    intersects with the sprite's projected x range
*/
static int	check_hit_collision(int center_x, double transform_y,
	double transform_x)
{
	int	sprite_screen_x;
	int	sprite_width;
	int	draw_start_x;
	int	draw_end_x;

	sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));
	sprite_width = abs((int)(WIN_H / transform_y));
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (center_x >= draw_start_x && center_x <= draw_end_x)
		return (1);
	return (0);
}

/*
    Process a single sprite for hit detection
    Returns 1 if hit, 0 otherwise
    If enemy is hit, deactivates it and increments win_game counter
*/
static int	process_single_sprite(t_game *g, t_sprite_data *sprite,
	double shot_range, int center_x)
{
	t_enemy	*enemy;
	double	sprite_x;
	double	sprite_y;
	double	trans[2];

	if (sprite->distance >= shot_range)
		return (0);
	enemy = &g->enemy_sys.enemies[sprite->index];
	sprite_x = enemy->x - g->player.x;
	sprite_y = enemy->y - g->player.y;
	calculate_transform(g, sprite_x, sprite_y, trans);
	if (trans[1] <= 0.0)
		return (0);
	if (check_hit_collision(center_x, trans[1], trans[0]))
	{
		enemy->active = 0;
		g->win_game++;
		return (1);
	}
	return (0);
}

/*
    Iterates over all active enemies and
    Check if an enemy is hit by the player's shot
    Uses z-buffer to determine shot range
*/
void	check_enemy_hit(t_game *g)
{
	t_sprite_data	sprites[MAX_ENEMIES];
	int				i;
	int				sprite_count;
	int				center_x;
	double			shot_range;

	center_x = WIN_W / 2;
	shot_range = g->z_buffer[center_x];
	prepare_sprite_data(g, sprites, &sprite_count);
	if (sprite_count > 0)
		qsort(sprites, sprite_count, sizeof(t_sprite_data),
			compare_sprites_nearest_first);
	i = 0;
	while (i < sprite_count)
	{
		if (process_single_sprite(g, &sprites[i], shot_range, center_x))
			return ;
		i++;
	}
}
