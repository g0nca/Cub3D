/* ************************************************************************** */
/*                                                                            */
/*   unified_sprite_rendering.c                        :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

typedef enum e_sprite_type
{
	SPRITE_ENEMY,
	SPRITE_DOOR
}	t_sprite_type;

typedef struct s_unified_sprite
{
	t_sprite_type	type;
	double			x;
	double			y;
	double			distance;
	int				index;  // índice no array de enemies ou doors
}	t_unified_sprite;

// Função de comparação para qsort (mais longe primeiro)
static int	compare_sprites_far_first(const void *a, const void *b)
{
	t_unified_sprite	*sa = (t_unified_sprite *)a;
	t_unified_sprite	*sb = (t_unified_sprite *)b;
	
	if (sa->distance > sb->distance)
		return (-1);
	if (sa->distance < sb->distance)
		return (1);
	return (0);
}

// Calcula distância do jogador ao sprite
static double	calculate_sprite_distance(t_game *g, double sprite_x, double sprite_y)
{
	double	dx;
	double	dy;
	
	dx = sprite_x - g->player.x;
	dy = sprite_y - g->player.y;
	return (sqrt(dx * dx + dy * dy));
}

// Coleta todos os sprites (enemies + doors) em um único array
static int	collect_all_sprites(t_game *g, t_unified_sprite *sprites)
{
	int	count;
	int	i;
	
	count = 0;
	
	// Adicionar inimigos
	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			sprites[count].type = SPRITE_ENEMY;
			sprites[count].x = g->enemy_sys.enemies[i].x;
			sprites[count].y = g->enemy_sys.enemies[i].y;
			sprites[count].distance = calculate_sprite_distance(g, 
				sprites[count].x, sprites[count].y);
			sprites[count].index = i;
			count++;
		}
		i++;
	}
	
	// Adicionar portas
	i = 0;
	while (i < g->door_sys.door_count)
	{
		sprites[count].type = SPRITE_DOOR;
		sprites[count].x = g->door_sys.doors[i].x + 0.5;
		sprites[count].y = g->door_sys.doors[i].y + 0.5;
		sprites[count].distance = calculate_sprite_distance(g,
			sprites[count].x, sprites[count].y);
		sprites[count].index = i;
		count++;
		i++;
	}
	
	return (count);
}

// Obtém a textura apropriada para a porta
static t_img	*get_door_texture(t_game *g, t_door *door)
{
	if (door->state == DOOR_CLOSED)
		return (&g->door_sys.closed_textures[0]);
	else if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
		return (&g->door_sys.opening_textures[door->frame]);
	else
		return (&g->door_sys.opening_textures[DOOR_FRAMES - 1]);
}

// Obtém a textura apropriada para o inimigo
static t_img	*get_enemy_texture(t_game *g, t_enemy *enemy)
{
	return (&g->enemy_sys.enemy_textures[enemy->enemy_type][enemy->current_frame]);
}

// Obtém cor do pixel da textura
static int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	char	*pixel;
	
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	
	pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
	return (*(int *)pixel);
}

// Verifica se a cor é transparente
static int	is_transparent(int color)
{
	return ((color & 0x00FFFFFF) == 0);
}

// Desenha uma coluna vertical do sprite
static void	draw_sprite_column(t_game *g, int x, double distance, 
								t_img *texture, int tex_x, int is_door)
{
	(void)is_door;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		tex_y;
	int		d;
	int		color;
	
	line_height = (int)(WIN_H / distance);
	draw_start = -line_height / 2 + WIN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	
	draw_end = line_height / 2 + WIN_H / 2;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	
	y = draw_start;
	while (y < draw_end)
	{
		d = (y) * 256 - WIN_H * 128 + line_height * 128;
		tex_y = ((d * texture->height) / line_height) / 256;
		color = get_texture_color(texture, tex_x, tex_y);
		
		// Para portas, verificar transparência; para inimigos também
		if (!is_transparent(color))
			my_mlx_pixel_put(&g->screen, x, y, color);
		y++;
	}
}

// Renderiza um sprite individual
static void	render_single_sprite(t_game *g, t_unified_sprite *sprite)
{
	double	dir_x = cos(g->player.angle);
	double	dir_y = sin(g->player.angle);
	double	plane_x = -dir_y * 0.66;
	double	plane_y = dir_x * 0.66;
	
	double	sprite_x = sprite->x - g->player.x;
	double	sprite_y = sprite->y - g->player.y;
	double	inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
	double	transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
	double	transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);
	
	if (transform_y <= 0)
		return;
	
	int		sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));
	//int		sprite_height = abs((int)(WIN_H / transform_y));
	int		sprite_width = abs((int)(WIN_H / transform_y));
	int		draw_start_x = -sprite_width / 2 + sprite_screen_x;
	int		draw_end_x = sprite_width / 2 + sprite_screen_x;
	
	if (draw_start_x < 0)
		draw_start_x = 0;
	if (draw_end_x >= WIN_W)
		draw_end_x = WIN_W - 1;
	
	t_img	*texture;
	int		is_door = 0;
	
	if (sprite->type == SPRITE_DOOR)
	{
		texture = get_door_texture(g, &g->door_sys.doors[sprite->index]);
		is_door = 1;
	}
	else
		texture = get_enemy_texture(g, &g->enemy_sys.enemies[sprite->index]);
	
	int	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) 
						* texture->width / sprite_width) / 256;
		
		// Verificar z-buffer para garantir que não desenhamos sobre paredes
		if (transform_y < g->z_buffer[stripe])
			draw_sprite_column(g, stripe, transform_y, texture, tex_x, is_door);
		stripe++;
	}
}

// Função principal que substitui render_enemies e render_doors
void	render_all_sprites(t_game *g)
{
	t_unified_sprite	sprites[MAX_ENEMIES + MAX_DOORS];
	int					sprite_count;
	int					i;
	
	// Coletar todos os sprites
	sprite_count = collect_all_sprites(g, sprites);
	
	// Ordenar por distância (mais longe primeiro)
	qsort(sprites, sprite_count, sizeof(t_unified_sprite), compare_sprites_far_first);
	
	// Renderizar todos os sprites na ordem correta
	i = 0;
	while (i < sprite_count)
	{
		render_single_sprite(g, &sprites[i]);
		i++;
	}
}