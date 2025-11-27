/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:41:32 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/27 16:52:27 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void draw_filled_circle(int cx, int cy, int radius, t_cube *data)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(&data->mlxstruct, cx + x, cy + y, 0xFF0000);
            }
        }
    }
}

void draw_tile(t_cube *data, int color, int x, int y)
{
	int boundx;
	int boundy;
	int savex;

	boundx = x + MINIMAP_SIZE;
	boundy = y + MINIMAP_SIZE;
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

int is_player(t_cube *data, int x, int y)
{
    if (x == (int)data->player.x && y == (int)data->player.y)
        return (1);
    return (0);
}

size_t get_longest_line(char **map, int *a)
{
    int i;
    size_t longest;

    i = 0;
    longest = 0;
    while (map[i])
    {
        if (ft_strlen(map[i]) > longest)
            longest = ft_strlen(map[i]);
        i++;
    }
    *a = i;
    return (longest);
}

void draw_frame(t_cube *data)
{
    int i;
    int j;
    int length;
    int width;

    i = 0;
    length = get_longest_line(data->map, &width);
    // data->scale_x = (double)MINIMAP_SIZE / length;
    // data->scale_y = (double)MINIMAP_SIZE / width;
    // data->minimap_size = fmin(data->scale_y, data->scale_x);
    while (i < width)
    {
        j = 0;
        while (j < length)
        {
            draw_tile(data, 0x000000, j * MINIMAP_SIZE, i * MINIMAP_SIZE);
            j++;
        }
        i++;
    }
}

void draw_minimap(t_cube *data)
{
    int i;
    int j;

    i = 0;
    draw_frame(data);
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == '1')
                draw_tile(data, 0x000000, j * MINIMAP_SIZE, i * MINIMAP_SIZE);
            else if (data->map[i][j] == '0')
                draw_tile(data, 0xFFFFFF, j * MINIMAP_SIZE, i * MINIMAP_SIZE);
            if (data->map[i][j] == 'D' && is_door_closed(data, j, i))
                draw_tile(data, 0xFF0000, j * MINIMAP_SIZE, i * MINIMAP_SIZE);
            else if (data->map[i][j] == 'D' && !is_door_closed(data, j, i))
                draw_tile(data, 0x950606, j * MINIMAP_SIZE, i * MINIMAP_SIZE);
            if (is_player(data, j, i))
                draw_filled_circle(data->player.x * MINIMAP_SIZE, data->player.y * MINIMAP_SIZE, 1, data);
            j++;
        }
        i++;
    }
}

int rendering(t_cube *data)
{
	update_player(data);
    render_frame(data);
    draw_minimap(data);
    mlx_put_image_to_window(data->mlxstruct.mlx, data->mlxstruct.win,
                            data->mlxstruct.img.img, 0, 0);
	return (0);
}

void destroy_all(t_cube *data)
{
    if (data->mlxstruct.win)
		mlx_destroy_window(data->mlxstruct.mlx, data->mlxstruct.win);
	if (data->mlxstruct.img.img)
		mlx_destroy_image(data->mlxstruct.mlx, data->mlxstruct.img.img);
	if (data->mlxstruct.mlx)
		mlx_destroy_display(data->mlxstruct.mlx);
	free(data->mlxstruct.mlx);
    exit(0);
}

t_door *get_units(t_cube *data, int x, int y)
{
    int i;

    i = 0;
    while (i < data->doors[i].count)
    {
        if (data->doors[i].x == x && data->doors[i].y == y)
            return &(data->doors[i]);
        i++;
    }
    return (NULL);
}

t_door *get_door_coordinates(t_cube *data)
{
    int x = 0;
    int y = 0;

    if (data->map[(int)data->player.y + 1][(int)data->player.x] == 'D')
    {
        x = (int)data->player.x;
        y = (int)data->player.y + 1;
    }
    else if (data->map[(int)data->player.y - 1][(int)data->player.x] == 'D')
    {
        x = (int)data->player.x;
        y = (int)data->player.y - 1;
    }
    else if (data->map[(int)data->player.y][(int)data->player.x + 1] == 'D')
    {
        x = (int)data->player.x + 1;
        y = (int)data->player.y;
    }
    else if (data->map[(int)data->player.y][(int)data->player.x - 1] == 'D')
    {
        x = (int)data->player.x - 1;
        y = (int)data->player.y;
    }
    return (get_units(data, x, y));
}

void open_close_door(t_cube *data)
{
    t_door *door;
    door = get_door_coordinates(data);
    if (!door)
        return ; // free all and exit
    if (door->open == 0)
        door->open = 1;
    else
        door->open = 0;
}

int is_next_door(t_cube *data)
{
    if (data->map[(int)data->player.y + 1][(int)data->player.x] == 'D'
        || data->map[(int)data->player.y - 1][(int)data->player.x] == 'D'
        || data->map[(int)data->player.y][(int)data->player.x + 1] == 'D'
        || data->map[(int)data->player.y][(int)data->player.x - 1] == 'D')
        return (1);
    return (0);
}

int handle_key_press(int keycode, t_cube *data)
{
    printf("%f / %f\n", data->player.x, data->player.y);
    if (keycode == 119)
        data->player.move_direction_front = 1;
    if (keycode == 115)
        data->player.move_direction_front = -1;
    if (keycode == 97)
        data->player.move_direction_side = 1;
    if (keycode == 100)
        data->player.move_direction_side = -1;
    if (keycode == 65363)
        data->player.turn_direction = 1;
    if (keycode == 65361)
        data->player.turn_direction = -1;
    if (keycode == 102 && is_next_door(data))
        open_close_door(data);
    if (keycode == 65307)
        destroy_all(data);
    return 0;
}

int handle_key_release(int keycode, t_cube *data)
{
    if (keycode == 119 || keycode == 115) data->player.move_direction_front = 0;
    if (keycode == 97 || keycode == 100)  data->player.move_direction_side = 0;
    if (keycode == 65363 || keycode == 65361) data->player.turn_direction = 0;
    return 0;
}

void render_map(t_mlx *mlxstruct, t_cube *data)
{
	mlxstruct->mlx = mlx_init();
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, WIDTH, HEIGHT, "cub3D");
	mlxstruct->img.img = mlx_new_image(mlxstruct->mlx, WIDTH, HEIGHT);
	mlxstruct->img.addr = mlx_get_data_addr(mlxstruct->img.img, &mlxstruct->img.bits_per_pixel, &mlxstruct->img.line_length,
											&mlxstruct->img.endian);
	mlx_hook(mlxstruct->win, 2, 1L<<0, handle_key_press, data);
	mlx_hook(mlxstruct->win, 3, 1L<<1, handle_key_release, data); 
	mlx_loop_hook(mlxstruct->mlx, rendering, data);
	mlx_loop(mlxstruct->mlx);
}