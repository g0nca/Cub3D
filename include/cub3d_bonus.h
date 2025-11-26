/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:28:59 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 14:28:59 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/* ========================================================================== */
/*                               INCLUDES                                     */
/* ========================================================================== */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <time.h>
# include "../libs/libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"

/* ========================================================================== */
/*                               DEFINES                                      */
/* ========================================================================== */

/* Window dimensions */
# define WIN_W			800
# define WIN_H			600
# define TILE_SIZE		20

/* Minimap settings */
# define MINIMAP_RADIUS	80
# define MINIMAP_SCALE	15
# define MINIMAP_X		100
# define MINIMAP_Y		100

/* Key codes */
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define MOUSE_SENS		0.002
# define MOUSE_DEAD_ZONE	1
# define KEY_E			101

/* Math constants */
# ifndef M_PI
#  define M_PI			3.14159265358979323846
# endif

/* Path and element identifiers */
# define PATH_MAX		4096
# define NO				1
# define SO				2
# define WE				3
# define EA				4
# define F				5
# define C				6

# define WEAPON_FRAMES 5

/* Enemy animation settings */
# define MAX_ENEMIES 50
# define ENEMY_TYPES 5
# define FRAMES_PER_ENEMY 5
# define COLLISION_DISTANCE 0.5
# define ENEMY_SIZE 0.3
# define ENEMY_SPEED 0.001
# define ENEMY_ANIM_SPEED 100

/* Doors Setting */
# define MAX_DOORS 50
# define DOOR_FRAMES 8
# define DOOR_ANIM_SPEED 3
# define MIN_DOOR_DISTANCE 2

/* ========================================================================== */
/*                               STRUCTURES                                   */
/* ========================================================================== */

typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct s_map
{
	char			**grid;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*floor_color;
	char			*ceiling_color;
	int				floor_rgb[3];
	int				ceiling_rgb[3];
	int				start_x;
	int				start_y;
	int				start;
	int				last_map_line;
	int				end;
	int				exit_flag;
	int				width;
	int				height;
	bool			player_p;
	struct s_cub	*cub_struct;
}					t_map;

typedef struct s_cub
{
	t_map			*map;
	void			*mlx;
	void			*win;
}					t_cub;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_textures
{
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
}					t_textures;

typedef struct s_enemy
{
	double	x;
	double	y;
	int		enemy_type;
	int		active;
	int		current_frame;
	long	last_frame_time;
	t_img	frames[FRAMES_PER_ENEMY];
}			t_enemy;

typedef struct s_sprite_data
{
	int		index;
	double	distance;
	double	x;
	double	y;
}			t_sprite_data;

typedef struct s_enemy_system
{
	t_enemy		enemies[MAX_ENEMIES];
	int			enemy_count;
	int			game_over;
	t_img		enemy_textures[ENEMY_TYPES][FRAMES_PER_ENEMY];
}				t_enemy_system;

typedef struct s_ray
{
	double			ray_angle;
	double			distance;
	int				hit_vertical;
	double			wall_x;
	int				is_door;
}					t_ray;

typedef struct s_weapon
{
	t_img	textures[5];
	int		is_firing;
	int		current_frame;
	long	last_frame_time;
}	t_weapon;

typedef struct s_ray_vars
{
	double	dx;
	double	dy;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
}	t_ray_vars;

typedef struct s_draw_vars
{
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_h;
	int		sprite_w;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_draw_vars;

typedef struct s_wall_ctx
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	step;
	double	tex_pos;
	t_img	*tex;
}	t_wall_ctx;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	r_dir_x;
	double	r_dir_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

typedef struct s_parse_ctx
{
	t_map	*map;
	char	**f_split;
	char	**c_split;
	int		mode;
}	t_parse_ctx;

typedef struct s_scale_ctx
{
	double	s_x;
	double	s_y;
	int		x_off;
	int		y_off;
	int		w;
	int		h;
}	t_scale_ctx;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
	int				frame;
	int				anim_counter;
	int				is_vertical;
}	t_door;

typedef enum e_sprite_type
{
	SPRITE_ENEMY,
	SPRITE_DOOR
}	t_sprite_type;

typedef struct s_spr_calc
{
	double	inv_det;
	double	transform_y;
	int		screen_x;
	int		width;
	int		start_x;
	int		end_x;
	t_img	*tex;
}	t_spr_calc;

typedef struct s_spr_draw
{
	int		line_h;
	int		start_y;
	int		end_y;
	int		tex_x;
}	t_spr_draw;

typedef struct s_unified_sprite
{
	t_sprite_type	type;
	double			x;
	double			y;
	double			distance;
	int				index;
}	t_unified_sprite;

typedef struct s_door_system
{
	int		textures_loaded;
	int		door_count;
	t_door	doors[MAX_DOORS];
	t_img	closed_textures[DOOR_FRAMES];
	t_img	opening_textures[DOOR_FRAMES];
	t_img	frame_texture;
}	t_door_system;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				keys[256];
	int				key_left;
	int				key_right;
	int				win_game;
	double			z_buffer[WIN_W];
	t_player		player;
	t_map			map;
	t_cub			cub;
	t_textures		textures;
	t_weapon		weapon;
	t_img			screen;
	t_enemy_system	enemy_sys;
	t_door_system	door_sys;
}					t_game;

/* ========================================================================== */
/*                          FUNCTION PROTOTYPES                               */
/* ========================================================================== */

/* ---------------------------- Events (events/) ---------------------------- */
int					handle_keys(t_game *g);
void				handle_render(t_game *g);
int					key_press(int key, t_game *g);
int					key_release(int key, t_game *g);
void				move_strafe(t_game *g, int dir);
void				move_forward_backward(t_game *g, int dir);
void				rotate_player(t_game *g, int dir);
int					close_window(t_game *g);
int					mouse_move(int x, int y, t_game *g);
void				hide_mouse_cursor(t_game *g);
void				show_mouse_cursor(t_game *g);

/* ------------------------- Initialization (init/) ------------------------- */
void				init_game(t_game *game);
void				init_images(t_game *g);

/* ---------------------------- Rendering (render/) ------------------------- */
void				draw_minimap(t_game *g);
void				draw_player(t_game *g);
void				render_3d_view(t_game *g);
int					is_wall_at(t_game *g, int x, int y);
void				draw_wall_stripe(t_game *g, int x, t_ray *ray);
t_img				*get_texture(t_game *g, t_ray *ray, double angle);

/* -------------------------- Memory Management (free/) --------------------- */
void				ft_free_all(t_cub *cub);
void				ft_free_map(char **map);
void				free_split_array(char **array);

/* ---------------------------- Parsing (parse/) ---------------------------- */
t_map				*read_file_parse(char **av, t_cub *cub);
t_map				*separate_map_info(t_map *map);
void				check_if_all_elements_exists(t_map *map);
int					check_map_closed(t_map *map);
int					return_fd(char **av, t_map *map);

/* ----------------------- Map Initialization (parse/) ---------------------- */
t_map				*init_map_struct(void);

/* ----------------------- Map Validation (parse/) -------------------------- */
int					find_player_position_parse(t_map *map, int *x, int *y);
char				**copy_map_grid(t_map *map);
int					flood_fill(t_map *map, char **map_copy, int x, int y);

/* ----------------------- Map Processing (parse/) -------------------------- */
t_map				*save_only_map_lines(t_map *map);

/* -------------------- Map Info Separation (parse/) ------------------------ */
int					check_map(t_map *map, int *i);
int					is_map_line(char *line, t_map *map);
int					check_info(char *line);
void				save_texture_or_color1(t_map *map,
						char *value, int info_status);
void				save_texture_or_color2(t_map *map, char *value, int info);
t_map				*save_info_to_map_struct(t_map *map, char *line, int info);

/* ----------------------- Parsing Utilities (parse/) ----------------------- */
int					map_height(t_map *map);
void				trim_newline_center(t_map *map, int flag);
void				trim_newline(char *str);
int					ft_line_count(char **av, t_map *map);
int					delete_spaces(char *line, int info_status);

/* ----------------------- Parsing Utilities 2 (PARSE/) --------------------- */
void				print_texture(int type);

/* -------------------- Element Validation (parse/) ------------------------- */
bool				verify_color_elements(t_map *map);
void				check_texture(t_map *map, char *line, int type);
bool				verify_texture_elements(t_map *map);
bool				check_elements(t_map *map);

/* --------------- Element Validation Helpers (parse/) ---------------------- */
void				safe_exit_ctx(char *msg, t_parse_ctx *ctx);
void				save_color_val(char *s, int i, t_parse_ctx *ctx);
void				colors_check(char **colors, t_parse_ctx *ctx);

/* ------------------------- File Utilities (utils/) ------------------------ */
int					ft_strcmp(const char *s1, const char *s2);

/* ------------------------ Input Validation (parse/) ----------------------- */
void				parsing_input(int ac, char **av);

/* ----------------------- Player Positioning (parse/) ---------------------- */
int					find_player_position(t_game *game);

/* ------------------------- General Utilities (utils/) --------------------- */
void				free_images(t_game *g);
void				clear_image(t_img *img, int color);
void				put_pixel_to_img(t_img *img, int x, int y, int color);
int					rgb_to_int(int r, int g, int b);
int					get_ceiling_color(t_game *g);
int					get_floor_color(t_game *g);

/* ------------------------- Error Handling (errors/) ----------------------- */
void				print_error_and_exit_without_free(const char *message,
						int exit_flag, t_map *map);
void				print_error_and_exit_free(const char *message,
						int exit_flag, t_map *map);

/* ------------------------ Enimies (enimy_system/) ------------------------- */
void				init_enemy_system(t_game *g);
void				load_enemy_textures(t_game *g);
int					is_valid_spawn_position(t_game *g, double x, double y);
void				spawn_enemies(t_game *g);
void				update_enemies(t_game *g);
void				render_enemies(t_game *g);
int					is_transparent(int color);
void				check_enemy_collision(t_game *g);
void				draw_game_over(t_game *g);
void				draw_enemy_counter(t_game *g);
int					count_floor_tiles(t_game *g);
int					get_enemy_count_by_tiles(int tile_count);

/* ----------------------------- Main (main.c) ------------------------------ */
int					main(int ac, char **av);
int					init_cub_struct(t_cub **cub, char **av);
void				setup_game_data(t_game *game, t_cub *cub);
void				init_player_if_needed(t_game *game);
void				init_game_render(t_game *game);
void				init_hooks(t_game *game);
void				print_map_struct(t_cub *cub, t_map *map);
void				init_weapon_assets(t_game *game);
void				update_weapon_animation(t_game *game);
long				get_current_time_ms(void);
void				render_weapon(t_game *game);
void				handle_shoot(t_game *game);
void				free_weapon_texture_system(t_game *g);
void				free_enemy_system(t_game *g);
void				check_enemy_hit(t_game *g);
int					compare_sprites_nearest_first(const void *a, const void *b);
void				draw_game_win(t_game *g);
void				init_door_system(t_game *g);
void				place_doors_randomly(t_game *g);
void				update_doors(t_game *g);
void				interact_with_door(t_game *g);
void				free_door_system(t_game *g);
int					is_valid_door_position(t_game *g, int x, int y);
int					get_door_at_position(t_game *g, int x, int y);
int					is_door_blocking(t_game *g, int x, int y);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				render_all_sprites(t_game *g);
#endif
