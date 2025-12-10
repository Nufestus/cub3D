# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 17:56:35 by aammisse          #+#    #+#              #
#    Updated: 2025/12/10 15:38:06 by aammisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror

SRCS = parsing/colors_directions.c GNL/get_next_line.c GNL/get_next_line_utils.c \
		cub3D.c parsing/check_map.c parsing/create_map.c parsing/create_player.c \
		parsing/ft_atoi.c parsing/ft_split.c parsing/ft_strtrim.c parsing/ft_substr.c \
		parsing/keys_map.c parsing/list_functions.c parsing/rendering.c ray_casting/raycasting.c \
		ray_casting/calcul_texture.c ray_casting/init_textures.c parsing/memory.c parsing/player_utils.c \
		parsing/colors_utils.c parsing/create_door.c ray_casting/dda_algorithm.c ray_casting/raycast_help.c \
		ray_casting/raycast_utils.c parsing/door_utils.c parsing/minimap.c ray_casting/sprite.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} minilibx-linux/libmlx.a -lm -lX11 -lXext -o $@

%.o: %.c cub3D.h
	${CC} ${FLAGS} -c $< -o $@

run:
	make && make clean
	@./cub3D maps/map.cub

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all