/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:58:56 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/18 14:59:06 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

long get_current_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void update_weapon_animation(t_game *game)
{
    if (!game->weapon.is_firing)
    {
        game->weapon.current_frame = 0; // Mostrar frame 0 (idle)
        return;
    }

    long current_time = get_current_time_ms();
    // Muda de frame a cada 80 milissegundos (ajusta este valor para a velocidade desejada)
    if (current_time - game->weapon.last_frame_time > 80) 
    {
        game->weapon.last_frame_time = current_time;
        game->weapon.current_frame++;

        // Se a animação terminou (chegou à frame 5)
        if (game->weapon.current_frame >= WEAPON_FRAMES)
        {
            game->weapon.current_frame = 0;  // Voltar para a frame 0
            game->weapon.is_firing = 0;      // Parar o estado de disparo
        }
    }
}