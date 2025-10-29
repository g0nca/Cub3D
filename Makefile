NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
MLX = -lmlx -lXext -lX11 -lm
SRC_DIR = src
OBJ_DIR = obj

SRC = main.c \
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette src include | grep -v OK || true

.PHONY: all clean fclean re norm run
