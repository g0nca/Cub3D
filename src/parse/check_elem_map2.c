/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem_map2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:40:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 15:49:12 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Sai do programa limpando a memória usando o contexto */
void	safe_exit_ctx(char *msg, t_parse_ctx *ctx)
{
	free_split_array(ctx->f_split);
	free_split_array(ctx->c_split);
	print_error_and_exit_free(msg, 1, ctx->map);
}

/* Salva o valor no mapa (RGB) */
void	save_color_val(char *s, int i, t_parse_ctx *ctx)
{
	int	val;

	val = ft_atoi(s);
	if (val < 0 || val > 255)
		safe_exit_ctx("The numbers exceed the valid range", ctx);
	if (ctx->mode == 1)
		ctx->map->floor_rgb[i] = val;
	else
		ctx->map->ceiling_rgb[i] = val;
}

/* Valida formatação da string */
static void	check_fmt(char *s, t_parse_ctx *ctx)
{
	int		j;
	bool	num;

	j = 0;
	num = false;
	while (s[j])
	{
		if (s[j] == '.')
			safe_exit_ctx("Invalid decimal numbers", ctx);
		if (s[j] == ' ' && !num && !s[j + 1])
			safe_exit_ctx("Missing numbers", ctx);
		if (s[j] >= '0' && s[j] <= '9')
			num = true;
		j++;
	}
}

/* Função principal: Recebe as cores e o contexto preparado */
void	colors_check(char **colors, t_parse_ctx *ctx)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		check_fmt(colors[i], ctx);
		save_color_val(colors[i], i, ctx);
		i++;
	}
	if (i != 3)
		safe_exit_ctx("Only 3 numbers are accepted", ctx);
}
