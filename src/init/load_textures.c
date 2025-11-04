/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:49 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 14:36:49 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void load_texture(void *mlx, t_img *img, char *path)
{
    img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
    if (!img->img)
        print_error_and_exit("Failed to load texture");
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

void    init_images(t_game *g)
{
    load_texture(g->mlx, &g->textures.north, "./assets/textures/north.xpm");
    load_texture(g->mlx, &g->textures.south, "./assets/textures/south.xpm");
    load_texture(g->mlx, &g->textures.west, "./assets/textures/west.xpm");
    load_texture(g->mlx, &g->textures.east, "./assets/textures/east.xpm");
}
