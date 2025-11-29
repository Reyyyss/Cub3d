# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/09 17:20:29 by hcarrasq          #+#    #+#              #
#    Updated: 2025/11/29 17:02:25 by hcarrasq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

# Directories
SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
MLX = ./minilibx-linux
MLX_A = $(MLX)/libmlx.a
PARSE_DIR = ./srcs/parsing
RENDER_DIR = ./srcs/render

# Source files
SRCS_FILES = 
PARSE_FILES = parse_main.c parser.c parsing_utils.c begin_data.c
RENDER_FILES = 

# Full paths
SRCS   = $(addprefix $(SRCS_DIR)/,   $(SRCS_FILES))
PARSE  = $(addprefix $(PARSE_DIR)/,  $(PARSE_FILES))
RENDER = $(addprefix $(RENDER_DIR)/, $(RENDER_FILES))
ALL_SRCS = $(SRCS) $(PARSE) $(RENDER)
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(ALL_SRCS:.c=.o)))

# Compiler and flags
CC = cc
CFLAGS =  -Iinclude -g -Wall -Wextra -Werror
MLXFLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

# Build targets
all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR) -s

$(MLX_A):
	$(MAKE) -C  $(MLX) -s
	
$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_A) $(MLXFLAGS) -o $(NAME)


$(OBJS_DIR)/%.o: $(PARSE_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: $(RENDER_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C  $(LIBFT_DIR) -s clean
	@$(MAKE) -C  $(MLX) -s clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) -s fclean
	@rm -rf $(NAME)

re: fclean all

r:
	make re && clear && ./$(NAME)

.PHONY: all clean fclean re r