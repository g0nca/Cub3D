/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:30:43 by andrade           #+#    #+#             */
/*   Updated: 2025/11/19 11:08:36 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Verifica se uma cor é transparente
 * Pixels com 'None' no XPM aparecem como preto (0x000000)
 * Você pode ajustar esta função se a cor for diferente
 */
int is_transparent(int color)
{
	// Remove o canal alpha se existir
	color = color & 0x00FFFFFF;

	// Verifica se é preto puro (cor transparente comum em XPM)
	if (color == 0x000000)
		return (1);

	// Verifica se é magenta (outra cor comum para transparência)
	if (color == 0xFF00FF)
		return (1);

	return (0);
}

/**
 * Compara sprites pela distância (para ordenação)
 */
static int	compare_sprites(const void *a, const void *b)
{
	t_sprite_data	*sa = (t_sprite_data *)a;
	t_sprite_data	*sb = (t_sprite_data *)b;

	if (sa->distance > sb->distance)
		return (-1);
	if (sa->distance < sb->distance)
		return (1);
	return (0);
}

/**
 * Renderiza um único sprite de inimigo - COM TRANSPARÊNCIA
 */
static void	render_sprite(t_game *g, t_enemy *enemy)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;

	// If texture not loaded, skip rendering
	if (!enemy->texture.img || !enemy->texture.addr)
		return;

	// Calcula posição relativa ao jogador
	sprite_x = enemy->x - g->player.x;
	sprite_y = enemy->y - g->player.y;

	// Calcula direção da câmera
	double dir_x = cos(g->player.angle);
	double dir_y = sin(g->player.angle);
	double plane_x = -dir_y * 0.66;  // FOV
	double plane_y = dir_x * 0.66;

	// Transforma sprite para espaço da câmera
	inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
	transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
	transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);

	// Sprite está atrás do jogador (não renderiza se estiver atrás)
	if (transform_y <= 0.0)
		return;

	// Calcula posição na tela
	sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));

	// Calcula altura do sprite
	sprite_height = abs((int)(WIN_H / transform_y));
	sprite_width = abs((int)(WIN_H / transform_y));

	// Calcula limites de desenho
	draw_start_y = -sprite_height / 2 + WIN_H / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + WIN_H / 2;
	if (draw_end_y >= WIN_H)
		draw_end_y = WIN_H - 1;

	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIN_W)
		draw_end_x = WIN_W - 1;

	// Desenha o sprite COM VERIFICAÇÃO DE TRANSPARÊNCIA
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		// Se a sprite estiver atrás da parede nessa coluna, pula
		if (stripe >= 0 && stripe < WIN_W)
		{
			if (transform_y >= g->z_buffer[stripe])
			{
				stripe++;
				continue;
			}
		}

		tex_x = (int)((stripe - (-sprite_width / 2 + sprite_screen_x)) *
			enemy->texture.width / sprite_width);

		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= enemy->texture.width)
			tex_x = enemy->texture.width - 1;

		y = draw_start_y;
		while (y < draw_end_y)
		{
			tex_y = ((y - draw_start_y) * enemy->texture.height) / sprite_height;

			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= enemy->texture.height)
				tex_y = enemy->texture.height - 1;

			color = *(int *)(enemy->texture.addr +
				(tex_y * enemy->texture.line_len +
				tex_x * (enemy->texture.bpp / 8)));

			// VERIFICA SE O PIXEL NÃO É TRANSPARENTE ANTES DE DESENHAR
			if (!is_transparent(color))
				put_pixel_to_img(&g->screen, stripe, y, color);

			y++;
		}
		stripe++;
	}
}

/**
 * Renderiza todos os inimigos (ordenados por distância)
 */
void	render_enemies(t_game *g)
{
	t_sprite_data	sprites[MAX_ENEMIES];
	int				i;
	int				sprite_count;

	if (g->enemy_sys.game_over)
		return;

	// Prepara dados dos sprites
	sprite_count = 0;
	i = 0;
	while (i < g->enemy_sys.enemy_count)
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

	// Ordena sprites por distância (mais longe primeiro)
	if (sprite_count > 0)
		qsort(sprites, sprite_count, sizeof(t_sprite_data), compare_sprites);
	i = 0;
	while (i < sprite_count)
	{
		render_sprite(g, &g->enemy_sys.enemies[sprites[i].index]);
		i++;
	}
}
