NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -Iinclude -Iminilibx-linux
MLX_DIR = minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = libs/get_next_line
GNL = $(GNL_DIR)/get_next_line.a
SRC_DIR = src
OBJ_DIR = obj

# Valgrind suppression file
SUPP_FILE = mlx_leaks.supp

# Lista todos os ficheiros .c na pasta src (adiciona os teus ficheiros aqui)
SRC = main.c \
        parse/parsing_input.c \
        parse/parsing_player.c \
        parse/read_file.c \
        parse/check_elem_map.c \
        parse/check_elem_map2.c \
        parse/init_map_struct.c \
        parse/utils_parse.c \
        parse/utils_parse2.c \
        parse/save_only_map_lines.c \
        parse/check_map_closed.c \
        parse/separate_map_info.c \
        parse/save_texture_or_color.c \
        utils/file_utils.c \
        utils/errors.c \
        utils/free_all.c \
		utils/free_images.c \
        utils/pixel_utils.c \
        utils/color_utils.c \
        events/handle_keys.c \
        events/move_player.c \
        events/rotate_player.c \
        events/mouse_control.c \
		events/gun_animation.c \
        init/init_game.c \
        init/load_textures.c \
        render/draw_minimap.c \
        render/draw_player.c \
        render/draw_walls.c \
        render/raycasting.c \
		render/render_weapon.c \
        enemy_system/enemy_init.c \
        enemy_system/enemy_spawn.c \
        enemy_system/enemy_render.c \
        enemy_system/enemy_collision.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Cores para output
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(SUPP_FILE) $(NAME)


sup_file: 
	$(file > sup, $(SUP_BODY))
	@echo "${BOLD_YELLOW}Suppressing mousemove leaks${END}"

# Cria arquivo de supressão para leaks do MLX
define SUP_BODY
{
	mlx_mouse_hide_leak
	Memcheck:Leak
	match-leak-kinds: reachable
	fun:mlx_mouse_hide
}
{
	XrmGetStringDatabase_leak
	Memcheck:Leak
	match-leak-kinds: reachable
	fun:XrmGetStringDatabase
}
{
	_dl_open_leak
	Memcheck:Leak
	match-leak-kinds: reachable
	fun:_dl_open
}
{
	_XrmInitParseInfo_leak
	Memcheck:Leak
	match-leak-kinds: reachable
	fun:_XrmInitParseInfo
}
endef


$(SUPP_FILE):
	@echo "$(YELLOW)A criar ficheiro de supressão Valgrind...$(RESET)"
	@echo "$$SUP_BODY" > $(SUPP_FILE)
	@echo "$(GREEN)✓ Ficheiro de supressão criado: $(SUPP_FILE)$(RESET)"
# Compila a minilibx primeiro
$(MLX_DIR)/libmlx.a:
	@echo "$(BLUE)A compilar MinilibX...$(RESET)"
	@make -C $(MLX_DIR)
	@echo "$(GREEN)MinilibX compilada!$(RESET)"

# Cria objetos na pasta obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)A compilar $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compila o executável
$(NAME): $(MLX_DIR)/libmlx.a $(OBJ) $(GNL) $(LIBFT)
	@echo "$(BLUE)A criar executável $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(MLX) $(GNL) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

$(GNL):
	@$(MAKE) -C $(GNL_DIR) --no-print-directory
	@echo "$(GREEN)✅ GNL.a built successfully!$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ libft.a built successfully!$(RESET)"

# Limpa objetos
clean:
	@echo "$(RED)A remover objetos...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(SUPP_FILE)
	@make -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) fclean --no-print-directory
	@echo "$(GREEN)Objetos removidos!$(RESET)"

# Limpa tudo
fclean: clean
	@echo "$(RED)A remover executável...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(SUPP_FILE)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) fclean --no-print-directory
	@echo "$(GREEN)Limpeza completa!$(RESET)"

# Recompila tudo
re: fclean all

# Verifica norminette
norm:
	@echo "$(BLUE)A verificar norminette...$(RESET)"
	@norminette src include | grep -v OK || true

# Compila e executa
run: all
	@if [ -z "$(MAP)" ]; then \
		echo "$(RED)Erro: Especifica um mapa com MAP=caminho/mapa.cub$(RESET)"; \
		echo "$(YELLOW)Exemplo: make run MAP=maps/test.cub$(RESET)"; \
		exit 1; \
	fi
	./$(NAME) $(MAP)

# Executa com Valgrind usando supressões
valgrind: $(NAME) $(SUPP_FILE)
	@if [ -z "$(MAP)" ]; then \
		echo "$(RED)Erro: Especifica um mapa com MAP=caminho/mapa.cub$(RESET)"; \
		echo "$(YELLOW)Exemplo: make valgrind MAP=maps/test.cub$(RESET)"; \
		exit 1; \
	fi
	@echo "$(YELLOW)A executar Valgrind com supressão de leaks do MLX...$(RESET)"
	@valgrind --leak-check=full \
			  --show-leak-kinds=all \
			  --track-origins=yes \
			  --suppressions=$(SUPP_FILE) \
			  ./$(NAME) $(MAP)

.PHONY: all clean fclean re norm run valgrind valgrind-full