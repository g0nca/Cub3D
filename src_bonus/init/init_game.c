/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:35 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/* Helper: Apenas define os caminhos das texturas */
static void	setup_weapon_paths(char **paths)
{
	paths[0] = "assets/gun_textures/gun0.xpm";
	paths[1] = "assets/gun_textures/gun1.xpm";
	paths[2] = "assets/gun_textures/gun2.xpm";
	paths[3] = "assets/gun_textures/gun3.xpm";
	paths[4] = "assets/gun_textures/gun4.xpm";
}

/* Helper: Carrega uma frame específica e verifica erros */
static void	load_weapon_frame(t_game *g, int i, char *path)
{
	t_img	*tex;

	tex = &g->weapon.textures[i];
	tex->img = mlx_xpm_file_to_image(g->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		print_error_and_exit_without_free("Failed loading weapon textures",
			0, g->cub.map);
		close_window(g);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

/* Carrega as texturas da arma */
void	init_weapon_assets(t_game *game)
{
	char	*paths[WEAPON_FRAMES];
	int		i;

	setup_weapon_paths(paths);
	i = 0;
	while (i < WEAPON_FRAMES)
	{
		load_weapon_frame(game, i, paths[i]);
		i++;
	}
	game->weapon.is_firing = 0;
	game->weapon.current_frame = 0;
}

static void	init_keys(t_game *game)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		game->keys[i] = 0;
		i++;
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		print_error_and_exit_free("mlx_init failed", 1, NULL);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cub3D");
	if (!game->win)
		print_error_and_exit_free("mlx_init failed", 1, NULL);
	game->screen.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->screen.img)
		print_error_and_exit_free("mlx_init failed", 1, NULL);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	init_images(game);
	init_weapon_assets(game);
	init_door_system(game);
	game->win_game = 0;
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.angle = 0.0;
	game->player.move_speed = 0.02;
	game->player.rot_speed = 0.01;
	init_keys(game);
	game->key_left = 0;
	game->key_right = 0;
}
