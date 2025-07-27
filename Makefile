# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 17:56:35 by aammisse          #+#    #+#              #
#    Updated: 2025/07/26 16:55:13 by mouerchi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRCS = parsing/colors_directions.c GNL/get_next_line.c GNL/get_next_line_utils.c \
		cub3D.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} libmlx.a -framework OpenGL -framework AppKit -o $@

%.o: %.c cub3D.h
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all