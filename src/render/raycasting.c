/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:36 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/12 09:53:40 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int is_wall_at(t_game *g, int x, int y)
{
    if (y < 0 || x < 0 || !g->map.grid[y] || x >= (int)ft_strlen(g->map.grid[y]))
        return (1);
    return (g->map.grid[y][x] == '1');
}

// Algoritmo DDA (Digital Differential Analyzer) para raycasting preciso
static void cast_ray_dda(t_game *g, t_ray *ray, double angle)
{
    // Posição inicial
    int map_x = (int)g->player.x;
    int map_y = (int)g->player.y;

    // Direção do raio
    double ray_dir_x = cos(angle);
    double ray_dir_y = sin(angle);

    // Distância que o raio tem que percorrer para ir de uma linha x/y à próxima
    double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
    double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

    // Direção do passo e distância inicial até próxima linha
    int step_x;
    int step_y;
    double side_dist_x;
    double side_dist_y;

    // Calcula step e side_dist inicial
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (g->player.x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - g->player.x) * delta_dist_x;
    }

    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (g->player.y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - g->player.y) * delta_dist_y;
    }

    // Executa DDA
    int hit = 0;
    int side = 0;  // 0 = vertical (NS), 1 = horizontal (EW)

    while (!hit)
    {
        // Avança para próximo quadrado do mapa
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;  // Hit numa parede vertical
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;  // Hit numa parede horizontal
        }

        // Verifica se bateu numa parede
        if (is_wall_at(g, map_x, map_y))
            hit = 1;
    }

    // Calcula distância da parede
    if (side == 0)
        ray->distance = (side_dist_x - delta_dist_x);
    else
        ray->distance = (side_dist_y - delta_dist_y);

    // Calcula onde exatamente a parede foi atingida
    if (side == 0)
        ray->wall_x = g->player.y + ray->distance * ray_dir_y;
    else
        ray->wall_x = g->player.x + ray->distance * ray_dir_x;

    ray->wall_x -= floor(ray->wall_x);

    // Determina se foi parede vertical ou horizontal
    ray->hit_vertical = (side == 0);
    ray->ray_angle = angle;
}

static t_img *get_texture(t_game *g, t_ray *ray, double angle)
{
    if (ray->hit_vertical)
    {
        // Parede vertical (Norte/Sul)
        if (cos(angle) > 0)
            return (&g->textures.east);
        else
            return (&g->textures.west);
    }
    else
    {
        // Parede horizontal (Este/Oeste)
        if (sin(angle) > 0)
            return (&g->textures.south);
        else
            return (&g->textures.north);
    }
}

static void draw_wall_stripe(t_game *g, int x, t_ray *ray)
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


void render_3d_view(t_game *g)
{
    double fov = M_PI / 3;  // 60 graus
    double angle_step = fov / WIN_W;
    double ray_angle = g->player.angle - fov / 2;

    int x = 0;
    while (x < WIN_W)
    {
        t_ray ray;
        cast_ray_dda(g, &ray, ray_angle);
        draw_wall_stripe(g, x, &ray);
        ray_angle += angle_step;
        x++;
    }
}
