/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 14:57:28 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void free_images(t_game *g)
{
    if (g->textures.north.img)
        mlx_destroy_image(g->mlx, g->textures.north.img);
    if (g->textures.south.img)
        mlx_destroy_image(g->mlx, g->textures.south.img);
    if (g->textures.west.img)
        mlx_destroy_image(g->mlx, g->textures.west.img);
    if (g->textures.east.img)
        mlx_destroy_image(g->mlx, g->textures.east.img);
}
