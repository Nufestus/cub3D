/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:41:32 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/24 14:59:03 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int rendering(t_cube *data)
{
	update_player(data);
    render_frame(data);
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

int handle_key_press(int keycode, t_cube *data)
{
    if (keycode == 119) // W
        data->player.move_direction_front = 1;
    if (keycode == 115) // S
        data->player.move_direction_front = -1;
    if (keycode == 97)  // A
        data->player.move_direction_side = 1;
    if (keycode == 100) // D
        data->player.move_direction_side = -1;
    if (keycode == 65363) // Left Arrow
        data->player.turn_direction = 1;
    if (keycode == 65361) // Right Arrow
        data->player.turn_direction = -1;
    if (keycode == 65307) // ESC
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