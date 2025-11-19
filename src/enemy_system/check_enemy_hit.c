/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemy_hit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:40:59 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/19 15:21:24 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#include <math.h>
#include <stdlib.h> // Para qsort

// ... (A função compare_sprites_nearest_first que definimos antes) ...
int compare_sprites_nearest_first(const void *a, const void *b)
{
    double distance_a = ((t_sprite_data *)a)->distance;
    double distance_b = ((t_sprite_data *)b)->distance;

    if (distance_a < distance_b)
        return (-1);
    else if (distance_a > distance_b)
        return (1);
    else
        return (0);
}


void check_enemy_hit(t_game *g)
{
    t_sprite_data   sprites[MAX_ENEMIES];
    int             i;
    int             sprite_count;
    int             center_x = WIN_W / 2;
    double  sprite_x;
    double  sprite_y;
    double  inv_det;
    double  transform_x;
    double  transform_y;


    double shot_range = g->z_buffer[center_x]; 

    // 1. Prepara dados dos sprites
    sprite_count = 0;
    i = 0;
    while (i < MAX_ENEMIES)
    {
        if (g->enemy_sys.enemies[i].active)
        {
            sprites[sprite_count].index = i;
            sprites[sprite_count].x = g->enemy_sys.enemies[i].x;
            sprites[sprite_count].y = g->enemy_sys.enemies[i].y;
            sprites[sprite_count].distance = sqrt(
                pow(g->player.x - sprites[sprite_count].x, 2) +
                pow(g->player.y - sprites[sprite_count].y, 2)
            );
            sprite_count++;
        }
        i++;
    }

    // 2. Ordena sprites por distância (MAIS PRÓXIMO primeiro desta vez!)
    if (sprite_count > 0)
        qsort(sprites, sprite_count, sizeof(t_sprite_data), compare_sprites_nearest_first);

    // 3. Itera e verifica o impacto (Hitscan)
    i = 0;
    while (i < sprite_count)
    {
        int current_index = sprites[i].index;
        t_enemy *enemy = &g->enemy_sys.enemies[current_index];

        if (sprites[i].distance >= shot_range)
        {
            i++;
            continue;
        }

        // MATEMÁTICA DE PROJEÇÃO
        sprite_x = enemy->x - g->player.x;
        sprite_y = enemy->y - g->player.y;
        
        // Usamos as direções e plano da câmara armazenados na tua estrutura (assumindo que tens)
        // Se nao tiveres, teras de calcular dir_x, dir_y, plane_x, plane_y aqui
        // (Copiei o calculo da tua funcao render_sprite original)
        double dir_x = cos(g->player.angle);
        double dir_y = sin(g->player.angle);
        double plane_x = -dir_y * 0.66;  // FOV
        double plane_y = dir_x * 0.66;

        inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
        transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
        transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);

        if (transform_y <= 0.0)
        {
            i++;
            continue;
        }
        int sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));
        int sprite_width = abs((int)(WIN_H / transform_y));
        int draw_start_x = -sprite_width / 2 + sprite_screen_x;
        int draw_end_x = sprite_width / 2 + sprite_screen_x;

        if (center_x >= draw_start_x && center_x <= draw_end_x)
        {
            enemy->active = 0;
			g->win_game++;
            printf("Inimigo %d morto!\n", current_index);
            return ;
        }
        i++;
    }
}
