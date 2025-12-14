# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 17:56:35 by aammisse          #+#    #+#              #
#    Updated: 2025/12/14 13:54:11 by aammisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror

SRCS = parsing/colors_directions_bonus.c GNL/get_next_line_bonus.c GNL/get_next_line_utils_bonus.c \
		cub3D_bonus.c parsing/check_map_bonus.c parsing/create_map_bonus.c parsing/create_player_bonus.c \
		parsing/ft_atoi_bonus.c parsing/ft_split_bonus.c parsing/ft_strtrim_bonus.c parsing/ft_substr_bonus.c \
		parsing/keys_map_bonus.c parsing/list_functions_bonus.c parsing/rendering_bonus.c ray_casting/raycasting_bonus.c \
		ray_casting/calcul_texture_bonus.c ray_casting/init_textures_bonus.c parsing/memory_bonus.c parsing/player_utils_bonus.c \
		parsing/colors_utils_bonus.c parsing/create_door_bonus.c ray_casting/dda_algorithm_bonus.c ray_casting/raycast_help_bonus.c \
		ray_casting/raycast_utils_bonus.c parsing/door_utils_bonus.c parsing/minimap_bonus.c ray_casting/sprite_bonus.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@make -C minilibx-linux
	@${CC} ${FLAGS} ${OBJS} ./minilibx-linux/libmlx.a -lm -lX11 -lXext -o $@
	@echo "\033[1;31m✔ Compilation Done ( ͡° ͜ʖ ͡°)\033[0m"

%.o: %.c cub3D_bonus.h
	@${CC} ${FLAGS} -c $< -o $@
	@echo "\033[0;32m➤ $< \033[1;32mDONE [✓]"

run:
	@make
	@./cub3D maps/map.cub
	@make fclean

clean:
	@rm -rf ${OBJS}
	@make clean -C minilibx-linux

fclean: clean
	@rm -rf ${NAME}

re: fclean all