/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:01:46 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 15:41:37 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/*
** Removemos a variavel 'pixel' para ficar apenas com 4 variaveis.
** O cálculo do endereço é feito diretamente na atribuição de 'color'.
*/
static void	draw_scaled_line(t_img *dest, t_img *src,
	t_scale_ctx *c, int y_dest)
{
	int				x_dest;
	int				x_src;
	int				y_src;
	unsigned int	color;

	y_src = (int)floor(y_dest * c->s_y);
	if (y_src < 0 || y_src >= src->height)
		return ;
	x_dest = 0;
	while (x_dest < c->w)
	{
		x_src = (int)floor(x_dest * c->s_x);
		if (x_src >= 0 && x_src < src->width)
		{
			color = *(unsigned int *)(src->addr + (y_src * src->line_len
						+ x_src * (src->bpp / 8)));
			if (!is_transparent(color))
				put_pixel_to_img(dest, x_dest + c->x_off,
					y_dest + c->y_off, color);
		}
		x_dest++;
	}
}

/*
** Agora recebe apenas 3 argumentos (dest, src, ctx).
** Todos os dados de dimensão estão dentro de 'ctx'.
*/
static void	scale_and_copy_img_to_buffer(t_img *dest, t_img *src,
			t_scale_ctx *ctx)
{
	int	y_dest;

	if (!src || !dest)
		return ;
	y_dest = 0;
	while (y_dest < ctx->h)
	{
		draw_scaled_line(dest, src, ctx, y_dest);
		y_dest++;
	}
}

/*
** Preenche a struct 'ctx' aqui para evitar variáveis soltas
** e passar muitos argumentos para a próxima função.
*/
void	render_weapon(t_game *game)
{
	t_scale_ctx	ctx;
	t_img		*tex;

	tex = &game->weapon.textures[game->weapon.current_frame];
	if (!tex->img)
		return ;
	ctx.w = (int)(WIN_W * 0.4);
	ctx.h = (int)(tex->height * ((double)ctx.w / tex->width));
	ctx.x_off = WIN_W / 2 - ctx.w / 2;
	ctx.y_off = WIN_H - ctx.h + 20;
	ctx.s_x = (double)tex->width / ctx.w;
	ctx.s_y = (double)tex->height / ctx.h;
	scale_and_copy_img_to_buffer(&game->screen, tex, &ctx);
}

void	handle_shoot(t_game *game)
{
	if (game->weapon.is_firing)
		return ;
	game->weapon.is_firing = 1;
	game->weapon.current_frame = 1;
	game->weapon.last_frame_time = get_current_time_ms();
	check_enemy_hit(game);
}
