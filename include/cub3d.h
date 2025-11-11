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

#define MINIMAP_RADIUS 80      // Raio do minimapa circular
#define MINIMAP_SCALE 15       // Escala do minimapa (pixels por tile)
#define MINIMAP_X 100          // Posição X do centro do minimapa
#define MINIMAP_Y 100          // Posição Y do centro do minimapa

// Define key codes
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

#define M_PI 3.14159265358979323846
#include "../libs/get_next_line/get_next_line.h"

#define PATH_MAX 4096

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	move_speed;
	double	rot_speed;
}			t_player;
#define NO 1
#define SO 2
#define WE 3
#define EA 4
#define F 5
#define C 6

typedef struct s_map
{
	char	**grid;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    char    *floor_color;
    char    *ceiling_color;
    int     floor_rgb[3];
    int     ceiling_rgb[3];
    int     start;
    int     last_map_line;
    int     end;
    int     exit_flag;
    int     width;
    int     height;
    struct s_cub   *cub_struct;
}   t_map;

typedef struct s_cub
{
    t_map   *map;
    void    *mlx;
    void    *win;
}   t_cub;


typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	west;
	t_img	east;
}			t_textures;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int		hit_vertical;
	double	wall_x;
}			t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			keys[256];
	int			key_left;
	int			key_right;
	t_player	player;
	t_map		map;
	t_cub		cub;
	t_textures	textures;
	t_img		screen;
}				t_game;

/* typedef struct s_data
{
    int     flag_exit;
    char    *file_path;
}               t_data; */

//events
int		handle_keys(t_game *g);
int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);
void	move_strafe(t_game *g, int dir);
void	move_forward_backward(t_game *g, int dir);
void	rotate_player(t_game *g, int dir);
int		close_window(t_game *g);

//intit
void	init_game(t_game *game);
void	init_images(t_game *g);

//render
void	draw_minimap(t_game *g);
void	draw_player(t_game *g);
void	render_3d_view(t_game *g);

// free_all.c
void	ft_free_all(t_cub *cub);
void	ft_free_map(char **map);
void free_split_array(char **array);

// parse/read_file.c
t_map	*read_file_parse(char **av, t_cub *cub);
t_map	*init_map_struct(void);
t_map   *separate_map_info(t_map *map);
t_map	*save_info_to_map_struct(t_map *map, char *line, int info_status);
int		check_info(char *line);
int		check_map(t_map *map, int *i);
int		is_map_line(char *line);
bool    check_elements(t_map *map);
void	trim_newline(char *str);
void	save_texture_or_color2(t_map *map, char *value, int info_status);
bool	verify_texture_elements(t_map *map);
void	check_texture(t_map *map, char *line);
//void    colors_check(char **colors, t_map *map, int floor_or_ceiling);
//void	save_color_values(char *colors, t_map *map, int floor_or_ceiling, int i);
// utils/file_utils.c
int		ft_strcmp(const char *s1, const char *s2);

// parsing_input.c
void	parsing_input(int ac, char **av);

//parse
int		find_player_position(t_game *game);

//utils
void	free_images(t_game *g);
void	clear_image(t_img *img, int color);
void	put_pixel_to_img(t_img *img, int x, int y, int color);

// errors.c
void    print_error_and_exit_without_free(const char *message, int exit_flag, t_map *map);
void    print_error_and_exit_FREE(const char *message, int exit_flag, t_map *map);

int		main(int ac, char **av);

#endif
