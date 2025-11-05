/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:36 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/05 09:32:04 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int is_wall_at(t_game *g, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    if (map_y < 0 || map_x < 0 || !g->map.grid[map_y] ||
        map_x >= (int)ft_strlen(g->map.grid[map_y]))
        return (1);
    return (g->map.grid[map_y][map_x] == '1');
}

static void cast_ray(t_game *g, t_ray *ray, double angle)
{
    double step = 0.01;
    double x = g->player.x;
    double y = g->player.y;
    double dx = cos(angle) * step;
    double dy = sin(angle) * step;

    ray->ray_angle = angle;
    ray->distance = 0;

    while (ray->distance < 20)
    {
        x += dx;
        y += dy;
        ray->distance += step;

        if (is_wall_at(g, x, y))
        {
            double dx_wall = x - floor(x);
            double dy_wall = y - floor(y);
            ray->hit_vertical = (fabs(dx_wall) < 0.01 || fabs(dx_wall - 1) < 0.01);
            ray->wall_x = ray->hit_vertical ? dy_wall : dx_wall;
            break;
        }
    }
}

static t_img *get_texture(t_game *g, t_ray *ray, double angle)
{
    if (ray->hit_vertical)
    {
        if (cos(angle) > 0)
            return (&g->textures.east);
        else
            return (&g->textures.west);
    }
    else
    {
        if (sin(angle) > 0)
            return (&g->textures.south);
        else
            return (&g->textures.north);
    }
}

static void draw_wall_stripe(t_game *g, int x, t_ray *ray)
{
    double corrected_dist = ray->distance * cos(ray->ray_angle - g->player.angle);
    int wall_height = (int)(WIN_H / corrected_dist);
    int draw_start = (WIN_H - wall_height) / 2;
    int draw_end = draw_start + wall_height;

    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= WIN_H)
        draw_end = WIN_H - 1;

    t_img *texture = get_texture(g, ray, ray->ray_angle);
    int tex_x = (int)(ray->wall_x * texture->width);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;

    // Desenha teto
    for (int y = 0; y < draw_start; y++)
        put_pixel_to_img(&g->screen, x, y, 0x87CEEB);

    // Desenha parede com textura
    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)((y - draw_start) * texture->height / wall_height);
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= texture->height)
            tex_y = texture->height - 1;
        int color = *(int *)(texture->addr + (tex_y * texture->line_len +
                    tex_x * (texture->bpp / 8)));
        put_pixel_to_img(&g->screen, x, y, color);
    }

    // Desenha chão
    for (int y = draw_end; y < WIN_H; y++)
        put_pixel_to_img(&g->screen, x, y, 0x8B4513);
}

void    render_3d_view(t_game *g)
{
    double fov = M_PI / 3;
    double angle_step = fov / WIN_W;
    double ray_angle = g->player.angle - fov / 2;

    for (int x = 0; x < WIN_W; x++)
    {
        t_ray ray;
        cast_ray(g, &ray, ray_angle);
        draw_wall_stripe(g, x, &ray);
        ray_angle += angle_step;
    }
}
