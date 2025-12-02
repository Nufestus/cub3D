# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 17:56:35 by aammisse          #+#    #+#              #
#    Updated: 2025/11/30 15:24:30 by aammisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRCS = parsing/colors_directions.c GNL/get_next_line.c GNL/get_next_line_utils.c \
		cub3D.c parsing/check_map.c parsing/create_map.c parsing/create_player.c \
		parsing/ft_atoi.c parsing/ft_split.c parsing/ft_strtrim.c parsing/ft_substr.c \
		parsing/keys_map.c parsing/list_functions.c parsing/rendering.c ray_casting/raycasting.c \
		textures/calcul_texture.c textures/init_textures.c

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