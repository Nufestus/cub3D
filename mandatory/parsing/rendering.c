/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:41:32 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/01 12:53:51 by aammisse         ###   ########.fr       */
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

int is_player(t_cube *data, int x, int y)
{
    if (x == (int)data->player.x && y == (int)data->player.y)
        return (1);
    return (0);
}

int rendering(t_cube *data)
{
	update_player(data);
    draw_floor_and_ceiling(data);
    render_frame(data);
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
    if (keycode == 65307)
        destroy_all(data);
    return 0;
}

int handle_close(t_cube *data)
{
    destroy_all(data);
    return (0);
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
    init_textures(data);
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, WIDTH, HEIGHT, "cub3D");
	mlxstruct->img.img = mlx_new_image(mlxstruct->mlx, WIDTH, HEIGHT);
	mlxstruct->img.addr = mlx_get_data_addr(mlxstruct->img.img, &mlxstruct->img.bits_per_pixel, &mlxstruct->img.line_length,
											&mlxstruct->img.endian);
	mlx_hook(mlxstruct->win, 2, 1L<<0, handle_key_press, data);
	mlx_hook(mlxstruct->win, 3, 1L<<1, handle_key_release, data);
    mlx_hook(mlxstruct->win, 17, 0, handle_close, data); 
	mlx_loop_hook(mlxstruct->mlx, rendering, data);
	mlx_loop(mlxstruct->mlx);
}