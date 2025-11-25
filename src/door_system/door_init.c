/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:39:08 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/25 13:05:08 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	load_door_textures(t_game *g)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		snprintf(path, sizeof(path), "assets/door_textures/door_closed%d.xpm", i);
		g->door_sys.closed_textures[i].img = mlx_xpm_file_to_image(g->mlx,
			path, &g->door_sys.closed_textures[i].width,
			&g->door_sys.closed_textures[i].height);
		if (!g->door_sys.closed_textures[i].img)
		{
			print_error_and_exit_without_free("Failed loading door textures",
				0, g->cub.map);
			close_window(g);
		}
		g->door_sys.closed_textures[i].addr = mlx_get_data_addr(
			g->door_sys.closed_textures[i].img,
			&g->door_sys.closed_textures[i].bpp,
			&g->door_sys.closed_textures[i].line_len,
			&g->door_sys.closed_textures[i].endian);
		i++;
	}
}

static void	load_opening_textures(t_game *g)
{
	char	path[256];
	int		i;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		snprintf(path, sizeof(path), "assets/door_textures/door_open%d.xpm", i);
		g->door_sys.opening_textures[i].img = mlx_xpm_file_to_image(g->mlx,
			path, &g->door_sys.opening_textures[i].width,
			&g->door_sys.opening_textures[i].height);
		if (!g->door_sys.opening_textures[i].img)
		{
			print_error_and_exit_without_free("Failed loading door textures",
				0, g->cub.map);
			close_window(g);
		}
		g->door_sys.opening_textures[i].addr = mlx_get_data_addr(
			g->door_sys.opening_textures[i].img,
			&g->door_sys.opening_textures[i].bpp,
			&g->door_sys.opening_textures[i].line_len,
			&g->door_sys.opening_textures[i].endian);
		i++;
	}
}

void	init_door_system(t_game *g)
{
	int	i;

	i = 0;
	while (i < MAX_DOORS)
	{
		g->door_sys.doors[i].x = -1;
		g->door_sys.doors[i].y = -1;
		g->door_sys.doors[i].state = DOOR_CLOSED;
		g->door_sys.doors[i].frame = 0;
		g->door_sys.doors[i].anim_counter = 0;
		g->door_sys.doors[i].is_vertical = 0;
		i++;
	}
	g->door_sys.door_count = 0;
	g->door_sys.textures_loaded = 0;
	load_door_textures(g);
	load_opening_textures(g);
	g->door_sys.textures_loaded = 1;
	place_doors_randomly(g);
}

void	free_door_system(t_game *g)
{
	int	i;

	if (!g->door_sys.textures_loaded)
		return ;
	i = 0;
	while (i < DOOR_FRAMES)
	{
		if (g->door_sys.closed_textures[i].img)
			mlx_destroy_image(g->mlx, g->door_sys.closed_textures[i].img);
		if (g->door_sys.opening_textures[i].img)
			mlx_destroy_image(g->mlx, g->door_sys.opening_textures[i].img);
		i++;
	}
}
