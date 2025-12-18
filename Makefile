# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 08:50:12 by dgargant          #+#    #+#              #
#    Updated: 2025/12/15 10:25:49 by dgargant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	   = Cub3D
TEST_NAME  = test_cub3d

CC          = cc

#-fsanitize=leak -g3 -O0

INC         = includes/
CFLAGS      = -Wall -Wextra -Werror -fsanitize=leak -g3 -I$(INC)

OBJS_DIR    = objs/

# Colores
RED         = \033[0;31m
GREEN       = \033[0;92m
CYAN        = \033[0;96m
BLUE        = \033[0;34m
PURPLE      = \033[0;95m
YELLOW      = \033[0;93m
RESET       = \033[0m
BOLD_CYAN   = \033[1;96m

MLX	= ./MLX42-master
MLX_IN = -I$(MLX)/include
MLX_EX	= $(MLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

#LIBFT = libft.a
LIBFT_DIR   = ./libft/
LIBFT       = $(LIBFT_DIR)libft.a

SRCS_DIR    = src/

SRCS_FILES := \
	cub3D.c	\
	$(addprefix core/, draw_game.c	draw_map.c	draw_utils.c	init_textures.c	destroy.c)	\
	$(addprefix player/, init_player.c	movement.c)	\
	$(addprefix utils/, utils.c)	\
	$(addprefix map/, mapa_read.c	map_loading.c	map_init.c	map_cleanup.c	map_validation.c	maps_validations_utils.c)	\
	$(addprefix parsing/, element_parsing.c	parse_elements.c)	\
	get_next_line.c	\


OBJS_FILES  = $(SRCS_FILES:.c=.o)

SRCS        = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS        = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

all: $(NAME)

#libft/libft.a:
#	@make -C libft
#	@cp libft/bin/libft.a libft/libft.a
#	@cp libft/bin/libft.a .
#	@echo "$(GREEN)libft.a created!$(RESET)"

$(LIBFT):
	@echo "Compiling $(BLUE)libft$(RESET)\n"
	@make -sC $(LIBFT_DIR)


$(NAME): libmlx libft/libft.a $(OBJS)
	@echo "Compiling $(BLUE)$(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(MLX_IN) $(OBJS) $(MLX_EX) $(LIBFT) -o $(NAME)
	@echo "\n$(GREEN)$(NAME) compiled!$(RESET)"
	@echo "$(BOLD_CYAN)\n------------\n| Done! 👌 |\n------------$(RESET)"

libmlx:
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4
	@echo "$(BOLD_CYAN)\n------------\n| Done! 👌 |\n------------$(RESET)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(MLX)/build

fclean: clean
	rm -f $(NAME)
	@echo "$(GREEN)$(NAME)$(YELLOW) cleaned$(RESET)"

re: fclean all

test: test_main.c src/mapa_read.c src/get_next_line.c src/map_validation.c $(LIBFT)
	@echo "$(CYAN)Compiling test program...$(RESET)"
	$(CC) $(CFLAGS) test_main.c src/mapa_read.c src/get_next_line.c src/map_validation.c $(LIBFT) -o test_cub3d
	@echo "$(GREEN)Test program compiled!$(RESET)"

.PHONY: all clean fclean re test
.SILENT: all clean fclean
