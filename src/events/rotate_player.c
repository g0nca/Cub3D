/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:53 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 13:40:44 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_player(t_game *g, int dir)
{
	g->player.angle += g->player.rot_speed * dir;
	if (g->player.angle < 0)
		g->player.angle += 2 * M_PI;
	if (g->player.angle > 2 * M_PI)
		g->player.angle -= 2 * M_PI;
}
