/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:58:56 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/19 09:37:32 by ggomes-v         ###   ########.fr       */
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
    long current_time;

    if (!game->weapon.is_firing)
    {
        game->weapon.current_frame = 0;
        return;
    }
    current_time = get_current_time_ms();
    if (current_time - game->weapon.last_frame_time > 80) 
    {
        game->weapon.last_frame_time = current_time;
        game->weapon.current_frame++;
        if (game->weapon.current_frame >= WEAPON_FRAMES)
        {
            game->weapon.current_frame = 0;
            game->weapon.is_firing = 0;
        }
    }
}