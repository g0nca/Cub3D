/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:40:29 by ggomes-v            #+#    #+#             */
/*   Updated: 2025/11/03 15:40:29 by ggomes-v           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>
#include "../libs/libft/libft.h"
#include "../minilibx-linux/mlx.h"

#define WIN_W 800
#define WIN_H 600
#define TILE_SIZE 20
#define MINIMAP_SCALE 0.2

#define M_PI 3.14159265358979323846

#define PATH_MAX 4096

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	move_speed;
	double	rot_speed;
}			t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}			t_map;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   		t_img;

typedef struct s_textures
{
    t_img   north;
    t_img   south;
    t_img   west;
    t_img   east;
}   		t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
	t_textures	textures;
}	t_game;


/* typedef struct s_data
{
    int     flag_exit;
    char    *file_path;
}               t_data; */

//events
int handle_keys(int key, t_game *g);
void    move_strafe(t_game *g, int dir);
void    move_forward_backward(t_game *g, int dir);
void    rotate_player(t_game *g, int dir);
int close_window(t_game *g);

//intit
void    init_game(t_game *game);
void    init_images(t_game *g);

//render
void    draw_minimap(t_game *g);
void    draw_player(t_game *g);
void    render_3d_view(t_game *g);

// utils/file_utils.c
int	ft_strcmp(const char *s1, const char *s2);

// parsing_input.c
void    parsing_input(int ac, char **av);

//utils
void    free_images(t_game *g);

// errors.c
void    print_error_and_exit_without_free(const char *message, int exit_flag);
void    print_error_and_exit(const char *msg);

int     main(int ac, char **av);

#endif
