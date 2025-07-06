/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:57 by aammisse          #+#    #+#             */
/*   Updated: 2025/07/06 15:15:22 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "GNL/get_next_line.h"
#include "minilibx-linux/mlx.h"

typedef struct s_map
{
	char *line;
	struct s_map *next;
}				t_map;

typedef struct s_colors
{
	int r;
	int g;
	int b;
}				t_colors;

typedef struct	s_texture
{
	char *north;
	char *south;
	char *west;
	char *east;
	t_colors floorcolor;
	t_colors skycolor;
}				t_texture;

typedef struct	s_cube
{
	int mapfd;
	char *mapfile;
	char	**bomboclat;
	t_map *map;
	t_texture texture;
}				t_cube;

#endif