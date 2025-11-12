/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/12 09:59:54 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int is_wall_at(t_game *g, int x, int y)
{
    if (y < 0 || x < 0 || !g->map.grid[y] || x >= (int)ft_strlen(g->map.grid[y]))
        return (1);
    return (g->map.grid[y][x] == '1');
}

void draw_wall_stripe(t_game *g, int x, t_ray *ray)
{
    /* Corrige distorção do olho de peixe */
    double ang_diff = ray->ray_angle - g->player.angle;
    double corrected_dist = ray->distance * cos(ang_diff);

    /* Proteção contra distâncias muito pequenas (evita heights gigantes e div por zero) */
    if (corrected_dist < 0.0001)
        corrected_dist = 0.0001;

    /* Calcula altura da parede na tela (como double para evitar truncamento prematuro) */
    int wall_height = (int)((double)WIN_H / corrected_dist);

    int draw_start = (WIN_H - wall_height) / 2;
    int draw_end = draw_start + wall_height;

    if (draw_start < 0) draw_start = 0;
    if (draw_end >= WIN_H) draw_end = WIN_H - 1;

    /* Seleciona textura */
    t_img *texture = get_texture(g, ray, ray->ray_angle);

    /* tex_x em double -> depois convert para int; garante que não excede limites */
    int tex_x = (int)(ray->wall_x * (double)texture->width);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= texture->width) tex_x = texture->width - 1;

    /* Desenha teto */
    int y = 0;
    while (y < draw_start)
    {
        y++;
        put_pixel_to_img(&g->screen, x, y, get_ceiling_color(g));
    }

    /* Cálculo de passo para a textura (double!) */
    double step = (double)texture->height / (double)wall_height;
    /* Posição inicial na textura: o primeiro texel correspondente ao y = draw_start */
    double tex_pos = (draw_start - (WIN_H - wall_height) / 2.0) * step;
    /* alternativa clássica: tex_pos = (draw_start - WIN_H/2 + wall_height/2) * step; ambos equivalem */

    /* Desenha parede com amostragem correta */
    y = draw_start;
    while (y < draw_end)
    {
        y++;
        int tex_y = (int)tex_pos;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= texture->height) tex_y = texture->height - 1;

        int color = *(int *)(texture->addr +
                    (tex_y * texture->line_len + tex_x * (texture->bpp / 8)));

        put_pixel_to_img(&g->screen, x, y, color);
        tex_pos += step;
    }

    /* Desenha chão */
    y = draw_end;
    while (y < WIN_H)
    {
        y++;
        put_pixel_to_img(&g->screen, x, y, get_floor_color(g));
    }
}
