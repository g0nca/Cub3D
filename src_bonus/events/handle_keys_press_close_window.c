/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_press_close_window.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:52:07 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:22 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	key_press(int key, t_game *g)
{
	if (key == KEY_ESC)
		close_window(g);
	if (key >= 0 && key < 256)
		g->keys[key] = 1;
	if (key == 49 || key == 32)
		handle_shoot(g);
	if (key == KEY_LEFT)
		g->key_left = 1;
	if (key == KEY_RIGHT)
		g->key_right = 1;
	if (key == KEY_E)
		interact_with_door(g);
	return (0);
}

// Detecta quando uma tecla é solta
int	key_release(int key, t_game *g)
{
	if (key >= 0 && key < 256)
		g->keys[key] = 0;
	if (key == KEY_LEFT)
		g->key_left = 0;
	if (key == KEY_RIGHT)
		g->key_right = 0;
	return (0);
}

int	close_window(t_game *g)
{
	free_enemy_system(g);
	free_weapon_texture_system(g);
	free_door_system(g);
	free_images(g);
	if (g->screen.img)
		mlx_destroy_image(g->mlx, g->screen.img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	ft_free_all(&g->cub);
	exit(0);
	return (0);
}
