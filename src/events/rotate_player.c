/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:53 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 14:05:08 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    rotate_player(t_game *g, int dir)
{
    g->player.angle += g->player.rot_speed * dir;
    if (g->player.angle < 0)
        g->player.angle += 2 * M_PI;
    if (g->player.angle > 2 * M_PI)
        g->player.angle -= 2 * M_PI;
}
