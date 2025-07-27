/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:58:26 by aammisse          #+#    #+#             */
/*   Updated: 2025/07/26 17:34:02 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (dstsize == 0)
		return (len);
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (len);
}

static int handle(unsigned char c, unsigned char b)
{
	if (c - b > 0)
		return (1);
	else if (c - b < 0)
		return (-1);
	return (0);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	unsigned char *str1;
	unsigned char *str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return (handle(str1[i], str2[i]));
		i++;
	}
	return (0);
}

static int check_sign(int sign)
{
	if (sign < 0)
		return (0);
	else
		return (-1);
}

int ft_atoi(const char *str)
{
	long long result;
	long long old_result;
	int sign;
	int i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		old_result = result;
		result = result * 10 + (sign * (str[i] - '0'));
		if ((result / 10) != old_result)
			return (check_sign(sign));
		i++;
	}
	return (result);
}

static size_t count_words(char *s, char c)
{
	unsigned int i;
	size_t word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static size_t str_length(char const *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char **free_mem(char **s, int i)
{
	int index;

	index = 0;
	while (index < i)
	{
		free(s[index]);
		index++;
	}
	free(s);
	return (NULL);
}

char **ft_split(char const *s, char c)
{
	size_t k;
	size_t index;
	char **p;

	if (!s)
		return (NULL);
	k = count_words((char *)s, c);
	index = 0;
	p = (char **)malloc((sizeof(char *)) * (k + 1));
	if (!p)
		return (NULL);
	while (index < k)
	{
		while (*s == c)
			s++;
		p[index] = (char *)malloc((sizeof(char) * (str_length(s, c) + 1)));
		if (!p[index])
			return (free_mem(p, index));
		ft_strlcpy(p[index], s, str_length(s, c) + 1);
		s = s + str_length(s, c);
		index++;
	}
	p[index] = NULL;
	return (p);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t i;
	char *str;
	char *substr;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	str = (char *)s;
	if (start > i)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int parse_colors(char *str)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]) && str[i] != ',')
			return (1);
		if (str[i] == ',')
			check++;
		if (check > 2)
			return (1);
		i++;
	}
	return (0);
}

t_colors handle_colors(char *str, t_cube *data)
{
	t_colors rgb;
	int len;
	char *string;
	char **colors;

	(void)data;
	len = 2;
	while (str[len])
		len++;
	string = ft_substr(str, 2, len - 3);
	if (parse_colors(string))
		exit(120); // safe exit
	colors = ft_split(string, ',');
	rgb.r = ft_atoi(colors[0]);
	rgb.g = ft_atoi(colors[1]);
	rgb.b = ft_atoi(colors[2]);
	return rgb;
}

int check_ext(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i > 4)
	{
		str += i;
		str -= 4;
	}
	if (!strcmp(str, ".xpm") && i > 4)
		return (1);
	return (0);
}

char *handle_texture(char *str)
{
	int len;
	int start;
	char *copy;
	char *texture_file;

	start = 3;
	while (str[start] && isspace(str[start]))
		start++;
	len = start;
	while (str[len])
		len++;
	texture_file = ft_substr(str, start, len - 3);
	copy = texture_file;
	texture_file = ft_strtrim(texture_file, " \n");
	free(copy);
	if (!check_ext(texture_file))
		return (NULL);
	return (texture_file);
}

void handle_directions(char *str, t_cube *data, int *count)
{
	if (!ft_strncmp(str, "NO ", 3))
	{
		data->texture.north = handle_texture(str);
		(*count)++;
	}
	else if (!ft_strncmp(str, "SO ", 3))
	{
		data->texture.south = handle_texture(str);
		(*count)++;
	}
	else if (!ft_strncmp(str, "WE ", 3))
	{
		data->texture.west = handle_texture(str);
		(*count)++;
	}
	else if (!ft_strncmp(str, "EA ", 3))
	{
		data->texture.east = handle_texture(str);
		(*count)++;
	}
	else if (!ft_strncmp(str, "F ", 2))
	{
		data->texture.floor_color = handle_colors(str, data);
		(*count)++;
	}
	else if (!ft_strncmp(str, "C ", 2))
	{
		data->texture.sky_color = handle_colors(str, data);
		(*count)++;
	}
}

int openmap(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Unable to Open file!\n", 22);
		exit(1);
	}
	return (fd);
}

t_map *ft_lstlast(t_map *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void ft_lstadd_back(t_map **lst, t_map *new)
{
	if (!lst || !new)
		return;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_map *ft_lstnew(char *content)
{
	t_map *newnode;

	newnode = (t_map *)malloc(sizeof(t_map));
	if (!newnode)
		return (NULL);
	newnode->line = content;
	newnode->next = NULL;
	return (newnode);
}

void newnode(char *str, t_map **head)
{
	t_map *newnode;

	newnode = ft_lstnew(ft_strdup(str));
	ft_lstadd_back(head, newnode);
}

int check_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void read_from_map(t_cube *data)
{
	int count;
	int linecount;
	char *line;

	count = 0;
	linecount = 0;
	while ((line = get_next_line(data->map_fd)))
	{
		if (linecount >= 6 && count != 6)
			return;
		if (count < 6)
			handle_directions(line, data, &count);
		else if (count == 6)
			newnode(line, &data->list_map);
		if (strcmp(line, "\n") && check_space(line))
			linecount++;
		free(line);
	}
}

int ft_lstsize(t_map *lst)
{
	int i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

static char *alloc(char *str)
{
	int i;
	char *string;

	i = 0;
	string = (char *)malloc(ft_strlen(str) + 1);
	if (!string)
		return (NULL);
	while (str[i] != '\0')
	{
		string[i] = str[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static int in_set(char c, char *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *ft_strtrim(const char *s1, const char *set)
{
	size_t startind;
	size_t lastind;
	char *trim;

	if (s1 != NULL && set == NULL)
		return (alloc((char *)s1));
	else if ((s1 == NULL && set == NULL) || (s1 == NULL && set != NULL))
		return (NULL);
	startind = 0;
	lastind = ft_strlen((char *)s1) - 1;
	while (in_set(s1[startind], (char *)set) && s1[startind] != '\0')
		startind++;
	if (s1[startind] == '\0')
		return (ft_strdup(""));
	while (in_set(s1[lastind], (char *)set) && lastind > startind)
		lastind--;
	trim = (char *)malloc(lastind - startind + 2);
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, s1 + startind, lastind - startind + 2);
	return (trim);
}

void printmap(t_cube *data)
{
	printf("%s\n", data->texture.west);
	printf("%s\n", data->texture.south);
	printf("%s\n", data->texture.north);
	printf("%s\n", data->texture.east);
	printf("%d\n", data->texture.floor_color.r);
	printf("%d\n", data->texture.floor_color.g);
	printf("%d\n", data->texture.floor_color.b);
	printf("%d\n", data->texture.sky_color.r);
	printf("%d\n", data->texture.sky_color.g);
	printf("%d\n", data->texture.sky_color.b);
	int i = 0;
	while (data->map[i])
		printf("\"%s\"\n", data->map[i++]);
}

int count_without_space(t_map **ptr)
{
	int i;
	t_map *copy;

	i = 0;
	while (*ptr)
	{
		if ((*ptr)->line[0] == '\n' && (*ptr)->line[1] == '\0')
			(*ptr) = (*ptr)->next;
		else
			break;
	}
	copy = *ptr;
	while (copy)
	{
		if (copy->line[0] == '\n' && copy->line[1] == '\0')
			i++;
		else
			i = 0;
		copy = copy->next;
	}
	return (ft_lstsize(*ptr) - i);
}

void make_map(t_cube *data)
{
	int i;
	int len;
	t_map *ptr;

	i = 0;
	ptr = data->list_map;
	len = count_without_space(&ptr);
	data->map = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		// printf("%s", ptr->line);
		data->map[i] = ft_strdup(ft_strtrim(ptr->line, "\n"));
		i++;
		ptr = ptr->next;
	}
	data->map[i] = NULL;
}

int check_newline(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int check_top_bot(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == '0' || strchr("NSEW", map[0][i]))
			return (1);
		i++;
	}
	i = 0;
	while (map[i])
		i++;
	i--;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == '0' || strchr("NSEW", map[i][j]))
			return (1);
		j++;
	}
	return (0);
}

int check_edges(char **map)
{
	int i;

	if (check_top_bot(map))
		return (1);
	i = 0;
	while (map[i])
	{
		if (map[i][0] == '0' || map[i][ft_strlen(map[i]) - 1] == '0' || strchr("NSEW", map[i][0]) || strchr("NSEW", map[i][ft_strlen(map[i]) - 1]))
			return (1);
		i++;
	}
	return (0);
}

int lengthcalc(size_t a, char *string)
{
	if (a > ft_strlen(string) - 1)
		return 1;
	return (0);
}

int check_middle(char **map, t_cube *data)
{
	size_t i;
	size_t j;

	i = 0;
	data->width = 0;
	data->height = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == '0' || strchr("NSEW", map[i][j])) && ((map[i][j + 1] && map[i][j + 1] == ' ') || (j > 0 && map[i][j - 1] && map[i][j - 1] == ' ')))
				return (1);
			else if ((map[i][j] == '0' || strchr("NSEW", map[i][j])) && (((lengthcalc(j, map[i + 1])) || (i > 0 && lengthcalc(j, map[i - 1]))) || (i > 0 && map[i - 1][j] == ' ') || (map[i + 1] && map[i + 1][j] == ' ')))
				return (1);
			if (strchr("NSEW", map[i][j]))
			{
				data->playerx = j;
				data->playery = i;
				data->pixelx = calculate_pixel(data->playerx) + (TILE_SIZE / 2);
				data->pixely = calculate_pixel(data->playery) + (TILE_SIZE / 2);
				map[i][j] = '0';
			}
			j++;
			if ((int)j > data->width)
				data->width = j;
		}
		i++;
	}
	data->height = i;
	return (0);
}

int check_player(char **map)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (strchr("NSEW", map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count > 1 || !count)
		return (1);
	return (0);
}

int parse_map(t_cube *data)
{
	if (check_newline(data->map))
		return (1);
	if (check_player(data->map))
		return (1);
	if (check_edges(data->map))
		return (1);
	if (check_middle(data->map, data))
		return (1);
	return (0);
}

void create_map(t_cube *data)
{
	make_map(data);
	if (parse_map(data))
	{
		write(2, "Error\n", 7);
		exit(1);
	}
}

unsigned int get_pixel_address(t_mlx *mlx, int x, int y, t_cube *data)
{
	char *dst;

	dst = NULL;
	printf("%d / %d / %d / %d\n", x, y, data->width * TILE_SIZE, data->height * TILE_SIZE);
	if (x < 0 || y < 0 || x >= data->width * TILE_SIZE || y >= data->height * TILE_SIZE)
		return (0);
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_pixel / 8));
	printf("%d\n", *(unsigned int *)dst);
	return (*(unsigned int *)dst);
}

int handle_keys(int key, t_cube *data)
{

	printf("%d\n", get_pixel_address(data->mlxstruct.mlx, data->pixelx, data->pixely, data));
	if (key == ESC)
		exit(1);
	else if (key == W_KEY && get_pixel_address(data->mlxstruct.mlx, data->pixelx, data->pixely, data) != 0xFFFFFF)
		data->playery -= PLR_SPEED;
	// else if (key == S_KEY && data->map[plry2][(int)floor(data->playerx)] != '1')
	// 	data->playery += PLR_SPEED;
	// else if (key == D_KEY && data->map[(int)floor(data->playery)][plrx2] != '1')
	// 	data->playerx += PLR_SPEED;
	// else if (key == A_KEY && data->map[(int)floor(data->playery)][plrx1] != '1')
	// 	data->playerx -= PLR_SPEED;
	return (0);
}

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char *dst;

	dst = NULL;
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int calculate_pixel(double fract)
{
	return (fract * TILE_SIZE);
}

void draw_filled_circle(int cx, int cy, int radius, t_cube *data)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(&data->mlxstruct, cx + x, cy + y, 0x00FF00);
            }
        }
    }
}

void draw_tile(t_cube *data, int color, int x, int y)
{
	int boundx;
	int boundy;
	int savex;

	boundx = x + TILE_SIZE;
	boundy = y + TILE_SIZE;
	savex = x;

	while (y < boundy)
	{
		x = savex;
		while (x < boundx)
		{
			my_mlx_pixel_put(&data->mlxstruct, x, y, color);
			x++;
		}
		y++;
	}
}

int rendering(t_cube *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_tile(data, 0xFFFFFF, j * TILE_SIZE, i * TILE_SIZE);
			else if (data->map[i][j] == '0')
				draw_tile(data, 0x000000, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	// data->pixelx = calculate_pixel(data->playerx);
	// data->pixely = calculate_pixel(data->playery);
	draw_filled_circle(data->pixelx, data->pixely, 3, data);
	// int k  = 0;
	// while (data->map[k])
	// {
	// 	int f = 0;
	// 	while (data->map[k][f])
	// 	{
	// 		if (plrx == f * TILE_SIZE && plry == k * TILE_SIZE)

	// 		f++;
	// 	}
	// 	k++;
	// }
	mlx_put_image_to_window(data->mlxstruct.mlx, data->mlxstruct.win, data->mlxstruct.img.img, 0, 0);
	return (0);
}

void render_map(t_mlx *mlxstruct, t_cube *data)
{
	mlxstruct->mlx = mlx_init();
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, data->width * TILE_SIZE, data->height * TILE_SIZE, "cub3D");
	mlxstruct->img.img = mlx_new_image(mlxstruct->mlx, data->width * TILE_SIZE, data->height * TILE_SIZE);
	mlxstruct->img.addr = mlx_get_data_addr(mlxstruct->img.img, &mlxstruct->img.bits_per_pixel, &mlxstruct->img.line_length,
											&mlxstruct->img.endian);
	mlx_key_hook(mlxstruct->win, handle_keys, data);
	mlx_loop_hook(mlxstruct->mlx, rendering, data);
	mlx_loop(mlxstruct->mlx);
}

int main(int ac, char **av)
{
	t_cube data;

	if (ac != 2)
	{
		write(2, "Invalid File Map!\n", 19);
		return (1);
	}
	// initialize
	data.map_file = ft_strdup(av[1]);
	data.map_fd = openmap(av[1]);
	data.list_map = NULL;
	data.map = NULL;
	read_from_map(&data);
	create_map(&data);
	// open files
	printmap(&data);
	render_map(&data.mlxstruct, &data);
}