/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:49 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/11 11:55:27 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void load_texture(void *mlx, t_img *img, char *path)
{
    img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
    if (!img->img)
        print_error_and_exit_FREE("mlx_init failed", 1, NULL);
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

void    init_images(t_game *g)
{
    load_texture(g->mlx, &g->textures.north, "./assets/textures/north.xpm");
    load_texture(g->mlx, &g->textures.south, "./assets/textures/south.xpm");
    load_texture(g->mlx, &g->textures.west, "./assets/textures/west.xpm");
    load_texture(g->mlx, &g->textures.east, "./assets/textures/east.xpm");
}
