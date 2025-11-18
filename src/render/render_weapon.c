/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:01:46 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/18 15:46:03 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Assume que WIN_W e WIN_H estão definidos globalmente ou acessíveis

static void scale_and_copy_img_to_buffer(t_img *dest, t_img *src, int x_offset, int y_offset, int scale_width, int scale_height)
{
    int x_dest, y_dest;
    //char *dest_pixel;
    char *src_pixel;

    double scale_x_factor = (double)src->width / scale_width;
    double scale_y_factor = (double)src->height / scale_height;

    y_dest = 0;
    while (y_dest < scale_height)
    {
        x_dest = 0;
        while (x_dest < scale_width)
        {
            int x_src = (int)floor(x_dest * scale_x_factor);
            int y_src = (int)floor(y_dest * scale_y_factor);

            if (x_src >= 0 && x_src < src->width && y_src >= 0 && y_src < src->height)
            {
                src_pixel = src->addr + (y_src * src->line_len + x_src * (src->bpp / 8));
                unsigned int color = *(unsigned int *)src_pixel;

                // USA A TUA FUNCAO is_transparent AQUI
                if (!is_transparent(color)) 
                {
                    // Usa a tua funcao put_pixel_to_img para garantir consistencia
                    put_pixel_to_img(dest, x_dest + x_offset, y_dest + y_offset, color);
                }
            }
            x_dest++;
        }
        y_dest++;
    }
}

void render_weapon(t_game *game)
{
    t_img *texture_to_draw = &game->weapon.textures[game->weapon.current_frame];
    
    // Define o novo tamanho desejado: ex: 50% da largura da janela, ajuste a altura proporcionalmente
    // Ou usa um fator fixo como 2x o tamanho original
    int scaled_width = (int)(WIN_W * 0.4); // Exemplo: 40% da largura do ecra
    int scaled_height = (int)(texture_to_draw->height * ((double)scaled_width / texture_to_draw->width));

    // Calcula a posição de desenho (centrado horizontalmente, no fundo verticalmente)
    int x_pos = WIN_W / 2 - scaled_width / 2;
    int y_pos = WIN_H - scaled_height + 20; // +20 para descer um pouco mais se quiseres
    
    // Chama a nova função com os parâmetros de escala
    scale_and_copy_img_to_buffer(&game->screen, texture_to_draw, x_pos, y_pos, scaled_width, scaled_height); 
}



void handle_shoot(t_game *game)
{
    // Apenas permite disparar se a arma não estiver já a animar
    if (game->weapon.is_firing)
        return;

    game->weapon.is_firing = 1;
    game->weapon.current_frame = 1; // Começa na primeira frame de disparo (não a idle)
    game->weapon.last_frame_time = get_current_time_ms();

    // -- AQUI É ONDE VAIS INTEGRAR O HITSCAN (ver resposta anterior) --
    // O hitscan deve ocorrer no momento exato do disparo (nesta função ou na frame 1 da anim)
    //check_enemy_hit(game); 
}
