NAME = cub3D

CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3 -march=native -flto -ftree-vectorize -funroll-loops -ffast-math -g
MLXFLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRC_DIR = srcs
OBJECTS_DIR = objects

SOURCES_FILES = core/main.c core/mlx_init.c core/mlx_hooks.c \
				player/player.c player/player_movement.c \
				raycasting/rays.c raycasting/rays_init.c raycasting/rays_utils.c \
				raycasting/rays_collision.c raycasting/lines.c raycasting/math.c \
				rendering/render_3d.c rendering/textures.c rendering/texture_utils.c \
				minimap/mini_map.c minimap/mini_map_rays.c minimap/mini_map_utils.c \
				ui/game_instructions.c \
				parsing/parse_main.c parsing/parse_colors.c \
				parsing/parse_header.c parsing/checking_map.c \
				parsing/map_loading.c parsing/parsing_utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SOURCES_FILES))
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES_FILES:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ./libft

MLX = $(MLX_DIR)/libmlx.a
MLX_DIR = ./minilibx-linux

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS) 
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo ""
	@echo "\033[1;36m ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \033[0m"
	@echo "\033[1;36m██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\033[0m"
	@echo "\033[1;36m██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\033[0m"
	@echo "\033[1;36m██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\033[0m"
	@echo "\033[1;36m╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\033[0m"
	@echo "\033[1;36m ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \033[0m"
	@echo ""
	@echo "\033[1;32m  ✓ Build successful!\033[0m"
	@echo ""
	@echo "\033[1;33m  Usage:\033[0m ./cub3d maps/<choose avaliable map>"
	@echo "\033[0;37m  Available maps:\033[0m"
	@for map in maps/*.cub; do echo "    → $$map"; done
	@echo ""

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus -s --no-print-directory

$(MLX):
	@make -C $(MLX_DIR)

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)

clean:
	@rm -rf $(OBJECTS_DIR)
	@make -C $(LIBFT_DIR) clean -s

fclean: clean
	@echo "Cleaned!"
	@make -C $(LIBFT_DIR) fclean -s --no-print-directory
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re