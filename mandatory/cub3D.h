/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:57 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/01 13:03:33 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <time.h>
#include <math.h>
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
# define PLR_ROTATE 0.05
# define HITBOX 0.2
# define TEX_SIZE 64
# define SKY_OFFSET 0.25
# define SKY_SCALE 0.75

# define WIDTH 1024
# define HEIGHT 720

#define ESC 65307
#define W_KEY 119
#define S_KEY 115
#define D_KEY 100
#define A_KEY 97

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

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct    s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
	t_img	floor;
	t_img	sky;
    t_img	wall_N;
    t_img	wall_S;
    t_img	wall_E;
    t_img	wall_W;
    t_colors floor_color;
    t_colors sky_color;
}                t_texture;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	t_img img;
}				t_mlx;

typedef struct s_ray
{
	int mapX;
    int mapY;
	double cameraX;
	double rayDirX;
	double rayDirY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
}				t_ray;

typedef struct s_player
{
	double x;
	double y;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	int move_direction_front;
	int move_direction_side;
    int turn_direction;
}				t_player;

typedef struct	s_cube
{
	int pixelx;
	int pixely;
	int map_fd;
	char *map_file;
	char **map;
	t_ray ray;
	t_player player;
	t_map *list_map;
	t_mlx mlxstruct;
	t_texture texture;
}				t_cube;

void draw_floor_and_ceiling(t_cube *cube);
void init_textures(t_cube *data);
unsigned int get_pixel_color(t_img *img, int x, int y);
double	get_wallX(t_cube *data);
void	get_tex_info(t_cube *data, t_img **tex, int *tex_x);
void render_map(t_mlx *mlxstruct, t_cube *data);
int rendering(t_cube *data);
void newnode(char *str, t_map **head);
t_map *ft_lstnew(char *content);
int ft_lstsize(t_map *lst);
t_map *ft_lstlast(t_map *lst);
void ft_lstadd_back(t_map **lst, t_map *new);
int calculate_pixel(int fract);
unsigned int get_pixel_address(t_mlx *mlx, int x, int y, t_cube *data);
void my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color);
void free_double_array(char **s);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strtrim(const char *s1, const char *set);
char **ft_split(char const *s, char c);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_atoi(const char *str);
int openmap(char *str);
void create_map(t_cube *data);
int check_player(char **map);
int parse_map(t_cube *data);
int check_space(char *str);
void read_from_map(t_cube *data);
void printmap(t_cube *data);
int count_without_space(t_map **ptr);
void make_map(t_cube *data);
int parse_colors(char *str);
t_colors handle_colors(char *str, t_cube *data);
int check_ext(char *str);
char *handle_texture(char *str);
void handle_directions(char *str, t_cube *data, int *count);
int check_middle(char **map, t_cube *data);
void set_player(t_cube *data, int i, int j, char **map);
int lengthcalc(size_t a, char *string);
int check_edges(char **map);
int check_top_bot(char **map);
int check_newline(char **map);
void update_player(t_cube *data);
void render_frame(t_cube *data);

#endif