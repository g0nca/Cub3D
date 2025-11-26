/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:38:12 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 14:29:40 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/* Encontra a porta mais próxima usando cálculo direto para poupar variáveis */
static int	find_nearest_door(t_game *g)
{
	int		i;
	int		nearest;
	double	min;
	double	d;

	i = -1;
	nearest = -1;
	min = 2.0;
	while (++i < g->door_sys.door_count)
	{
		d = sqrt(pow(g->door_sys.doors[i].x + 0.5 - g->player.x, 2)
				+ pow(g->door_sys.doors[i].y + 0.5 - g->player.y, 2));
		if (d < min)
		{
			min = d;
			nearest = i;
		}
	}
	return (nearest);
}

/* Gere a interação (E) */
void	interact_with_door(t_game *g)
{
	int		idx;
	t_door	*d;

	idx = find_nearest_door(g);
	if (idx == -1)
		return ;
	d = &g->door_sys.doors[idx];
	if (d->state == DOOR_CLOSED)
	{
		d->state = DOOR_OPENING;
		d->frame = 0;
		d->anim_counter = 0;
	}
	else if (d->state == DOOR_OPEN)
	{
		d->state = DOOR_CLOSING;
		d->frame = DOOR_FRAMES - 1;
		d->anim_counter = 0;
	}
}

/* Auxiliar: Lógica de abrir porta */
static void	process_opening(t_door *d)
{
	d->anim_counter++;
	if (d->anim_counter >= DOOR_ANIM_SPEED)
	{
		d->frame++;
		d->anim_counter = 0;
		if (d->frame >= DOOR_FRAMES)
		{
			d->state = DOOR_OPEN;
			d->frame = DOOR_FRAMES - 1;
		}
	}
}

/* Auxiliar: Lógica de fechar porta */
static void	process_closing(t_door *d)
{
	d->anim_counter++;
	if (d->anim_counter >= DOOR_ANIM_SPEED)
	{
		d->frame--;
		d->anim_counter = 0;
		if (d->frame <= 0)
		{
			d->state = DOOR_CLOSED;
			d->frame = 0;
		}
	}
}

/* Loop principal de atualização */
void	update_doors(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->door_sys.door_count)
	{
		if (g->door_sys.doors[i].state == DOOR_OPENING)
			process_opening(&g->door_sys.doors[i]);
		else if (g->door_sys.doors[i].state == DOOR_CLOSING)
			process_closing(&g->door_sys.doors[i]);
		i++;
	}
}
