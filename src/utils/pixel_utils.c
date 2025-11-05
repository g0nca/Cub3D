/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:30:55 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/05 09:30:56 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    put_pixel_to_img(t_img *img, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

void    clear_image(t_img *img, int color)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_H)
    {
        x = 0;
        while (x < WIN_W)
        {
            put_pixel_to_img(img, x, y, color);
            x++;
        }
        y++;
    }
}
