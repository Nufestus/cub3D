/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:57 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 13:09:50 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "GNL/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define TILE_SIZE 20
# define PLR_ROTATE 0.05
# define HITBOX 0.2
# define TEX_SIZE 64

# define WIDTH 1024
# define HEIGHT 720

# define ESC 65307
# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define A_KEY 97

typedef struct s_door
{
	int	x;
	int	y;
	int	open;
	int	count;
}	t_door;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}				t_map;

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}				t_colors;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_torch
{
	t_img	torch[8];
	int		current_frame;
	int		timer;
}	t_torch;

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	t_torch		sprite;
	t_img		floor;
	t_img		wall_n;
	t_img		wall_s;
	t_img		wall_e;
	t_img		wall_w;
	t_img		door;
	t_colors	floor_color;
	t_colors	sky_color;
}				t_texture;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		door;
}				t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	speed;
	int		move_direction_front;
	int		move_direction_side;
	int		turn_direction;
}				t_player;

typedef struct s_dda
{
	t_img	*tex;
	int		color;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		drawstart;
	int		drawend;
	int		lineheight;
	int		y;
}			t_dda;

typedef struct s_sprite
{
	t_img	*image;
	int		x;
	int		y;
	int		start;
	int		end;
}			t_sprite;

typedef struct s_minimap
{
	int	map_h;
	int	map_w;
	int	dy;
	int	dx;
	int	map_x;
	int	map_y;
	int	draw_x;
	int	draw_y;
}		t_minimap;

typedef struct s_cube
{
	double		scale_x;
	double		scale_y;
	double		minimap_size;
	int			pixelx;
	int			pixely;
	int			map_fd;
	int			*dimensions;
	char		*map_file;
	char		**map;
	int			anime;
	int			mouse_x;
	int			dark;
	t_ray		ray;
	t_door		*doors;
	t_player	player;
	t_map		*list_map;
	t_mlx		mlxstruct;
	t_texture	texture;
}				t_cube;

int				ft_strcmp(const char *s1, const char *s2);
int				*make_array(t_cube *data);
void			get_map_dimensions(t_cube *data);
int				is_wall(t_cube *data, double x, double y);
int				get_map_height(char **map);
void			init_textures(t_cube *data);
unsigned int	get_pixel_color(t_img *img, int x, int y);
void			get_tex_info(t_cube *data, t_img **tex, int *tex_x);
void			create_doors(t_cube *data);
t_door			*get_units(t_cube *data, int x, int y);
void			render_map(t_mlx *mlxstruct, t_cube *data);
int				rendering(t_cube *data);
void			newnode(char *str, t_map **head);
t_map			*ft_lstnew(char *content);
int				ft_lstsize(t_map *lst);
t_map			*ft_lstlast(t_map *lst);
void			ft_lstadd_back(t_map **lst, t_map *new);
int				calculate_pixel(int fract);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color);
void			free_double_array(char **s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s1, const char *set);
char			**ft_split(char const *s, char c);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				openmap(t_cube *data);
void			create_map(t_cube *data);
void			check_player(char **map, t_cube *data);
int				parse_map(t_cube *data);
int				check_space(char *str);
void			read_from_map(t_cube *data);
int				count_without_space(t_map **ptr);
void			make_map(t_cube *data);
int				parse_colors(char *str);
t_colors		handle_colors(char *str, t_cube *data);
int				check_ext(char *str);
char			*handle_texture(char *str, t_cube *data);
void			handle_directions(char *str, t_cube *data, int *count);
int				check_middle(char **map, t_cube *data);
void			set_player(t_cube *data, int i, int j, char **map);
int				lengthcalc(size_t a, char *string);
int				check_edges(char **map);
int				check_top_bot(char **map);
int				check_newline(char **map);
void			update_player(t_cube *data);
int				is_closed(t_cube *data);
t_door			*get_units(t_cube *data, int x, int y);
int				is_door_closed(t_cube *data, double x, double y);
int				mouse_move(int x, int y, t_cube *data);
void			draw_floor_and_ceiling(t_cube *cube);
void			free_all(t_cube *data);
void			free_double_array(char **s);
void			free_textures(t_cube *data);
void			free_lst(t_map *head);
void			gnl_free(int fd);
int				ft_isalpha(char c);
void			destroy_all(t_cube *data);
char			*ft_strdup(const char *s);
int				collides(t_cube *data, double x, double y);
int				check_digits(char *str, int *i, int *count);
int				check_count(char *str, int *i, int *count);
int				check_ext(char *str);
void			assign_doors(t_cube *data);
void			initialize_values(int x, t_cube *data);
void			calculate_step(t_cube *data);
void			dda(t_cube *data);
void			set_resources(t_dda *dda, t_cube *data, int x);
void			draw_line(int x, t_cube *data);
void			set_darkness(t_cube *data, int *color);
void			cast_rays(t_cube *data);
void			draw_sprite(t_cube *data);
void			sprite_animation(t_cube *data);
int				create_rgb(t_colors *color);
void			move_back(t_cube *data, double newX, double newY);
void			move_right(t_cube *data, double newX, double newY);
void			move_left(t_cube *data, double newX, double newY);
void			rotate_left(t_cube *data);
void			rotate_right(t_cube *data);
void			draw_tile(t_cube *data, int color, int x, int y);
void			draw_filled_circle(int cx, int cy, int radius, t_cube *data);
void			safe_close_door(t_cube *data, t_door *door);
void			open_close_door(t_cube *data);
int				is_next_door(t_cube *data);
t_door			*get_door_coordinates(t_cube *data, int x, int y);
t_door			*get_units(t_cube *data, int x, int y);
void			draw_minimap(t_cube *data);
size_t			get_longest_line(char **map, int *a);
int				is_player(t_cube *data, int x, int y);
void			draw_pixel(t_cube *data, t_sprite *sprite);
#endif