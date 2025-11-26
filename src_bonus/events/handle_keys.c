/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:24 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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

void	handle_render(t_game *g)
{
	if (g->enemy_sys.game_over)
	{
		draw_game_over(g);
		return ;
	}
	update_weapon_animation(g);
	render_3d_view(g);
	render_all_sprites(g);
	render_weapon(g);
	draw_minimap(g);
	draw_player(g);
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
	draw_enemy_counter(g);
}

/**
 * Esta função é chamada continuamente pelo mlx_loop
 * AGORA OS INIMIGOS ATUALIZAM SEMPRE, NÃO SÓ QUANDO O PLAYER SE MOVE
 */
int	handle_keys(t_game *g)
{
	handle_movement(g);
	handle_rotation(g);
	update_enemies(g);
	update_doors(g);
	handle_render(g);
	if (g->win_game == g->enemy_sys.enemy_count)
		draw_game_win(g);
	return (0);
}

/* int handle_keys(t_game *g)
{
    //int movement_moved;
    //int rotation_moved;

    //movement_moved = handle_movement(g);
    //rotation_moved = handle_rotation(g);
	handle_movement(g);
	handle_rotation(g);
	//if (movement_moved)
    	update_enemies(g);
    handle_render(g);
	if (g->win_game == g->enemy_sys.enemy_count)
		draw_game_win(g);
    return (0);
} */
