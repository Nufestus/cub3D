/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:57 by aammisse          #+#    #+#             */
/*   Updated: 2025/07/12 13:40:16 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <time.h>
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

# define TILE_SIZE 30
# define PLR_SPEED 0.1

#define HEIGHT 800
#define WIDTH 800

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
	t_colors floor_color;
	t_colors sky_color;
}				t_texture;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	t_img img;
}				t_mlx;

typedef struct	s_cube
{
	int playerx;
	int playery;
	int width;
	int height;
	int map_fd;
	char *map_file;
	char **map;
	t_map *list_map;
	t_mlx mlxstruct;
	t_texture texture;
}				t_cube;

char	*ft_strtrim(const char *s1, const char *set);

#endif