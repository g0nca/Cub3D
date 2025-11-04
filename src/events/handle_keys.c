/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 15:10:45 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int handle_keys(int key, t_game *g)
{
    if (key == 65307) // ESC
        exit(0);
    else if (key == 119) // W
        move_forward_backward(g, 1);
    else if (key == 115) // S
        move_forward_backward(g, -1);
    else if (key == 97) // A
        move_strafe(g, -1);
    else if (key == 100) // D
        move_strafe(g, 1);
    else if (key == 65361) // left arrow
        rotate_player(g, -1);
    else if (key == 65363) // right arrow
        rotate_player(g, 1);

    mlx_clear_window(g->mlx, g->win);
    render_3d_view(g);      // ← Renderiza visão 3D primeiro
    draw_minimap(g);        // ← Minimap por cima
    draw_player(g);         // ← Player no minimap
    return (0);
}

int close_window(t_game *g)
{
    free_images(g);
    mlx_destroy_window(g->mlx, g->win);
    exit(0);
    return (0);
}
