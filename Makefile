# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgargant <dgargant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/29 08:50:12 by dgargant          #+#    #+#              #
#    Updated: 2025/08/29 11:15:14 by dgargant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	   = Cub3D

CC          = cc

#-fsanitize=thread -g3 -O0

INC         = includes/
CFLAGS      = -Wall -Wextra -Werror -g3 -I$(INC) $(LIBFT_IN) $(MLX_IN)

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

LIBFT	= ./libft
LIBFT_IN = -I$(LIBFT)/inc
LIBFT_EX	= $(LIBFT)/libft.a

SRCS_DIR    = src/

SRCS_FILES := \
	cub3D.c \
	mapa_read.c \
	get_next_line.c \
	get_next_line_utils.c \
	map_validation.c \
	parse_elements.c \
	init_variables.c

OBJS_FILES  = $(SRCS_FILES:.c=.o)

SRCS        = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS        = $(addprefix $(OBJS_DIR), $(OBJS_FILES))

all: $(NAME)

libmlx:
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4
	@echo "$(BOLD_CYAN)\n------------\n| Done! 👌 |\n------------$(RESET)"


$(NAME): libmlx $(OBJS)
	@echo "Compiling $(BLUE)$(NAME)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_EX) $(MLX_EX)  -o $(NAME)
	@echo "\n$(GREEN)$(NAME) compiled!$(RESET)"
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

.PHONY: all clean fclean re
.SILENT: all clean fclean
