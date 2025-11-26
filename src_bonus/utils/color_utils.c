/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:32:23 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:33 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/**
 * Converte valores RGB (0-255) para formato de cor hexadecimal
 * Formato: 0xRRGGBB
 */
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/**
 * Obtém a cor do teto a partir do array RGB
 */
int	get_ceiling_color(t_game *g)
{
	return (rgb_to_int(g->map.ceiling_rgb[0],
			g->map.ceiling_rgb[1],
			g->map.ceiling_rgb[2]));
}

/**
 * Obtém a cor do chão a partir do array RGB
 */
int	get_floor_color(t_game *g)
{
	return (rgb_to_int(g->map.floor_rgb[0],
			g->map.floor_rgb[1],
			g->map.floor_rgb[2]));
}
