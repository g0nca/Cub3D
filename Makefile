NAME = cub3d
CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx-linux
MLX_DIR = minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = libs/get_next_line
GNL = $(GNL_DIR)/get_next_line.a
SRC_DIR = src
OBJ_DIR = obj

# Lista todos os ficheiros .c na pasta src (adiciona os teus ficheiros aqui)
SRC = main.c \
	  parse/parsing_input.c \
	  utils/file_utils.c \
	  utils/errors.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Cores para output
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

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
$(NAME): $(MLX_DIR)/libmlx.a $(OBJ) $(LIBFT) $(GNL)
	@echo "$(BLUE)A criar executável $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(MLX) $(LIBFT) $(GNL) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

$(GNL):
	@$(MAKE) -C $(GNL_DIR) --no-print-directory
	@echo "$(BOLD_GREEN)✅ GNL.a built successfully!$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(BOLD_GREEN)✅ libft.a built successfully!$(RESET)"

# Limpa objetos
clean:
	@echo "$(RED)A remover objetos...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) fclean --no-print-directory
	@echo "$(GREEN)Objetos removidos!$(RESET)"

# Limpa tudo
fclean: clean
	@echo "$(RED)A remover executável...$(RESET)"
	@rm -f $(NAME)
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
	./$(NAME)

.PHONY: all clean fclean re norm run