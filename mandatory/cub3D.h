/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:08:57 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 13:47:01 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "GNL/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define TILE_SIZE 30
# define PLR_ROTATE 0.035
# define HITBOX 0.1
# define TEX_SIZE 64

# define WIDTH 1024
# define HEIGHT 720

# define ESC 65307
# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define A_KEY 97

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

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	t_img		wall_n;
	t_img		wall_s;
	t_img		wall_e;
	t_img		wall_w;
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

typedef struct s_cube
{
	int			pixelx;
	int			pixely;
	int			map_fd;
	char		*map_file;
	char		**map;
	int			*dimensions;
	t_ray		ray;
	t_player	player;
	t_map		*list_map;
	t_mlx		mlxstruct;
	t_texture	texture;
}				t_cube;

int				ft_strcmp(const char *s1, const char *s2);
int				check(t_cube *data, int x, int y);
int				*make_array(t_cube *data);
void			get_map_dimensions(t_cube *data);
int				is_wall(t_cube *data, double x, double y);
int				get_map_height(char **map);
int				create_rgb(t_colors *color);
int				collides(t_cube *data, double x, double y);
void			move_back(t_cube *data, double newX, double newY);
void			move_right(t_cube *data, double newX, double newY);
void			move_left(t_cube *data, double newX, double newY);
void			rotate_left(t_cube *data);
void			rotate_right(t_cube *data);
void			draw_line(int x, t_cube *data);
void			dda(t_cube *data);
void			calculate_step(t_cube *data);
void			initialize_values(int x, t_cube *data);
void			cast_rays(t_cube *data);
void			init_textures(t_cube *data);
unsigned int	get_pixel_color(t_img *img, int x, int y);
double			get_wallx(t_cube *data);
void			get_tex_info(t_cube *data, t_img **tex, int *tex_x);
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
void			free_all(t_cube *data);
void			free_textures(t_cube *data);
void			free_lst(t_map *head);
char			*ft_strdup(const char *s);
char			*ft_strtrim(const char *s1, const char *set);
void			gnl_free(int fd);
int				ft_isalpha(char c);
void			destroy_all(t_cube *data);
int				check_digits(char *str, int *i, int *count);
int				check_count(char *str, int *i, int *count);
int				check_ext(char *str);
#endif