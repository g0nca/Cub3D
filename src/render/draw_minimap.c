/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:33 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/18 09:21:33 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int is_inside_circle(int x, int y, int cx, int cy, int radius)
{
    int dx = x - cx;
    int dy = y - cy;
    return (dx * dx + dy * dy <= radius * radius);
}

static int get_map_tile(t_game *g, int map_x, int map_y)
{
    int     rows;
    char    tile;
    if (map_y < 0 || map_x < 0)
        return (1);    /* conta linhas de forma segura se não houver campo height */
    rows = 0;
    while (g->map.grid[rows])
        rows++;
    if (map_y >= rows)
        return (1);
    if (map_x >= (int)ft_strlen(g->map.grid[map_y]))
        return (1);
    tile = g->map.grid[map_y][map_x];
    if (tile == '1' || tile == ' ' || tile == '\t')
        return (1);
    return (g->map.grid[map_y][map_x] == '1');
}


static int get_minimap_color(t_game *g, double world_x, double world_y)
{
    int map_x = (int)world_x;
    int map_y = (int)world_y;

    if (get_map_tile(g, map_x, map_y))
        return (0x333333);  // Parede - cinzento escuro
    return (0xCCCCCC);      // Chão - cinzento claro
}

/* Desenha um marcador preenchido no minimapa (círculo pequeno) */
static void draw_enemy_marker(t_game *g, int cx, int cy, int color)
{
    int r = 2; // raio do marcador em pixels
    int x = -r;
    while (x <= r)
    {
        int y = -r;
        while (y <= r)
        {
            if (x * x + y * y <= r * r)
            {
                int px = cx + x;
                int py = cy + y;
                if (px >= 0 && px < WIN_W && py >= 0 && py < WIN_H)
                    put_pixel_to_img(&g->screen, px, py, color);
            }
            y++;
        }
        x++;
    }
}

void draw_minimap(t_game *g)
{
    int screen_x;
    int screen_y;
    int dx, dy;
    double world_x, world_y;

    // Desenha o círculo do minimapa
    screen_y = MINIMAP_Y - MINIMAP_RADIUS;
    while (screen_y <= MINIMAP_Y + MINIMAP_RADIUS)
    {
        screen_x = MINIMAP_X - MINIMAP_RADIUS;
        while (screen_x <= MINIMAP_X + MINIMAP_RADIUS)
        {
            if (is_inside_circle(screen_x, screen_y, MINIMAP_X, MINIMAP_Y, MINIMAP_RADIUS))
            {
                // Calcula offset do centro do minimapa
                dx = screen_x - MINIMAP_X;
                dy = screen_y - MINIMAP_Y;

                // Converte para coordenadas do mundo (centrado no jogador)
                world_x = g->player.x + (double)dx / MINIMAP_SCALE;
                world_y = g->player.y + (double)dy / MINIMAP_SCALE;

                // Obtém cor do tile
                int color = get_minimap_color(g, world_x, world_y);

                // Escurece pixels próximos da borda do círculo (efeito de vinheta)
                int dist_from_center = dx * dx + dy * dy;
                if (dist_from_center > (MINIMAP_RADIUS - 5) * (MINIMAP_RADIUS - 5))
                {
                    color = (color >> 1) & 0x7F7F7F;  // Escurece 50%
                }

                put_pixel_to_img(&g->screen, screen_x, screen_y, color);
            }
            screen_x++;
        }
        screen_y++;
    }

    // Desenha borda do minimapa
    screen_y = MINIMAP_Y - MINIMAP_RADIUS - 2;
    while (screen_y <= MINIMAP_Y + MINIMAP_RADIUS + 2)
    {
        screen_x = MINIMAP_X - MINIMAP_RADIUS - 2;
        while (screen_x <= MINIMAP_X + MINIMAP_RADIUS + 2)
        {
            dx = screen_x - MINIMAP_X;
            dy = screen_y - MINIMAP_Y;
            int dist_sq = dx * dx + dy * dy;

            // Desenha borda com 2 pixels de largura
            if (dist_sq <= (MINIMAP_RADIUS + 2) * (MINIMAP_RADIUS + 2) &&
                dist_sq >= (MINIMAP_RADIUS) * (MINIMAP_RADIUS))
            {
                put_pixel_to_img(&g->screen, screen_x, screen_y, 0x000000);
            }
            screen_x++;
        }
        screen_y++;
    }

    /* Desenha inimigos no minimapa (pequenos pontos vermelhos) */
    int i = 0;
    while (i < g->enemy_sys.enemy_count)
    {
        if (g->enemy_sys.enemies[i].active)
        {
            double ex = g->enemy_sys.enemies[i].x;
            double ey = g->enemy_sys.enemies[i].y;

            // Converte coordenadas do mundo para tela do minimapa
            int mx = MINIMAP_X + (int)((ex - g->player.x) * MINIMAP_SCALE);
            int my = MINIMAP_Y + (int)((ey - g->player.y) * MINIMAP_SCALE);

            // Só desenha se estiver dentro do círculo do minimapa
            if (is_inside_circle(mx, my, MINIMAP_X, MINIMAP_Y, MINIMAP_RADIUS))
            {
                draw_enemy_marker(g, mx, my, 0xFF0000);
            }
        }
        i++;
    }
}
