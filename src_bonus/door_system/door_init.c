/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:39:08 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 14:29:15 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/* Helper genérico para carregar uma textura XPM */
static void	load_asset(t_game *g, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		printf("Error: Failed to load texture: %s\n", path);
		print_error_and_exit_without_free("Asset Error", 0, g->cub.map);
		close_window(g);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
}

/* Carrega um array de texturas (animação) dado um padrão de nome */
static void	load_frames(t_game *g, t_img *arr, char *base_path)
{
	int		i;
	char	path[256];

	i = 0;
	while (i < DOOR_FRAMES)
	{
		snprintf(path, sizeof(path), base_path, i);
		load_asset(g, &arr[i], path);
		i++;
	}
}

/* Inicializa os dados das portas na estrutura */
static void	reset_doors(t_game *g)
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
}

/* Função Principal de Inicialização */
void	init_door_system(t_game *g)
{
	reset_doors(g);
	load_frames(g, g->door_sys.closed_textures,
		"assets/door_textures/door_closed%d.xpm");
	load_frames(g, g->door_sys.opening_textures,
		"assets/door_textures/door_open%d.xpm");
	g->door_sys.textures_loaded = 1;
	place_doors_randomly(g);
}

/* Liberta a memória */
void	free_door_system(t_game *g)
{
	int	i;

	if (!g->door_sys.textures_loaded)
		return ;
	if (g->door_sys.frame_texture.img)
		mlx_destroy_image(g->mlx, g->door_sys.frame_texture.img);
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
