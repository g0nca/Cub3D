/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/11 13:09:31 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Detecta quando uma tecla é pressionada
int	key_press(int key, t_game *g)
{
	if (key == KEY_ESC)
		close_window(g);
	// Teclas normais (W, A, S, D)
	if (key >= 0 && key < 256)
		g->keys[key] = 1;
	// Setas (teclas especiais)
	if (key == KEY_LEFT)
		g->key_left = 1;
	if (key == KEY_RIGHT)
		g->key_right = 1;
	return (0);
}

// Detecta quando uma tecla é solta
int	key_release(int key, t_game *g)
{
	// Teclas normais
	if (key >= 0 && key < 256)
		g->keys[key] = 0;
	// Setas (teclas especiais)
	if (key == KEY_LEFT)
		g->key_left = 0;
	if (key == KEY_RIGHT)
		g->key_right = 0;
	return (0);
}

static int	handle_movement(t_game *g)
{
	int	moved;

	moved = 0;
	if (g->keys[KEY_W])
	{
		move_forward_backward(g, 1);
		moved = 1;
	}
	if (g->keys[KEY_S])
	{
		move_forward_backward(g, -1);
		moved = 1;
	}
	if (g->keys[KEY_A])
	{
		move_strafe(g, -1);
		moved = 1;
	}
	if (g->keys[KEY_D])
	{
		move_strafe(g, 1);
		moved = 1;
	}
	return (moved);
}

static int	handle_rotation(t_game *g)
{
	int	moved;

	moved = 0;
	if (g->key_left)
	{
		rotate_player(g, -1);
		moved = 1;
	}
	if (g->key_right)
	{
		rotate_player(g, 1);
		moved = 1;
	}
	return (moved);
}

static void	handle_render(t_game *g)
{
	render_3d_view(g);
	draw_minimap(g);
	draw_player(g);
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
}

// Esta função é chamada continuamente pelo mlx_loop
int	handle_keys(t_game *g)
{
	int	moved;

	moved = 0;
	moved |= handle_movement(g);
	moved |= handle_rotation(g);
	if (moved)
		handle_render(g);
	return (0);
}

int	close_window(t_game *g)
{
	free_images(g);
	if (g->screen.img)
		mlx_destroy_image(g->mlx, g->screen.img);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	ft_free_all(&g->cub);
	exit(0);
	return (0);
}
