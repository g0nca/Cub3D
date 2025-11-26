/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:49 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:37 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static void	load_texture(void *mlx, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img)
		print_error_and_exit_free("mlx_init failed", 1, NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
}

void	init_images(t_game *g)
{
	load_texture(g->mlx, &g->textures.north, g->map.no_texture);
	load_texture(g->mlx, &g->textures.south, g->map.so_texture);
	load_texture(g->mlx, &g->textures.west, g->map.we_texture);
	load_texture(g->mlx, &g->textures.east, g->map.ea_texture);
}
