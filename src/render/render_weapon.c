/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:01:46 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/19 10:03:25 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void scale_and_copy_img_to_buffer(t_img *dest, t_img *src, int x_offset, int y_offset, int scale_width, int scale_height)
{
    int x_dest, y_dest;
    char *src_pixel;
    double scale_y_factor;
    double scale_x_factor;
    int x_src;
    int y_src;
    unsigned int color;

    scale_x_factor = (double)src->width / scale_width;
    scale_y_factor = (double)src->height / scale_height;

    y_dest = 0;
    while (y_dest < scale_height)
    {
        x_dest = 0;
        while (x_dest < scale_width)
        {
            x_src = (int)floor(x_dest * scale_x_factor);
            y_src = (int)floor(y_dest * scale_y_factor);

            if (x_src >= 0 && x_src < src->width && y_src >= 0 && y_src < src->height)
            {
                src_pixel = src->addr + (y_src * src->line_len + x_src * (src->bpp / 8));
                color = *(unsigned int *)src_pixel;
                if (!is_transparent(color)) 
                    put_pixel_to_img(dest, x_dest + x_offset, y_dest + y_offset, color);
            }
            x_dest++;
        }
        y_dest++;
    }
}

void render_weapon(t_game *game)
{
    t_img *texture_to_draw;
    int y_pos;
    int x_pos;
    int scaled_height;
    int scaled_width;

    texture_to_draw = &game->weapon.textures[game->weapon.current_frame];
    scaled_width = (int)(WIN_W * 0.4);
    scaled_height = (int)(texture_to_draw->height * ((double)scaled_width / texture_to_draw->width));
    x_pos = WIN_W / 2 - scaled_width / 2;
    y_pos = WIN_H - scaled_height + 20;
    scale_and_copy_img_to_buffer(&game->screen, texture_to_draw, x_pos, y_pos, scaled_width, scaled_height); 
}



void handle_shoot(t_game *game)
{
    if (game->weapon.is_firing)
        return;
    game->weapon.is_firing = 1;
    game->weapon.current_frame = 1;
    game->weapon.last_frame_time = get_current_time_ms();

    // -- AQUI É ONDE VAIS INTEGRAR O HITSCAN (ver resposta anterior) --
    // O hitscan deve ocorrer no momento exato do disparo (nesta função ou na frame 1 da anim)
    //check_enemy_hit(game); 
}
