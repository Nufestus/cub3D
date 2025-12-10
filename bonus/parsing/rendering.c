/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:41:32 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 16:29:34 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	rendering(t_cube *data)
{
	update_player(data);
	sprite_animation(data);
	cast_rays(data);
	draw_minimap(data);
	draw_sprite(data);
	mlx_put_image_to_window(data->mlxstruct.mlx, data->mlxstruct.win,
		data->mlxstruct.img.img, 0, 0);
	return (0);
}

int	handle_key_press(int keycode, t_cube *data)
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
	if (keycode == 102 && is_next_door(data))
		open_close_door(data);
	if (keycode == 99)
	{
		data->anime = 1;
		if (data->dark == 0)
			data->dark = 1;
		else
			data->dark = 0;
	}
	if (keycode == 65307)
		destroy_all(data);
	return (0);
}

int	handle_close(t_cube *data)
{
	destroy_all(data);
	return (0);
}

int	handle_key_release(int keycode, t_cube *data)
{
	if (keycode == 119 || keycode == 115)
		data->player.move_direction_front = 0;
	if (keycode == 97 || keycode == 100)
		data->player.move_direction_side = 0;
	if (keycode == 65363 || keycode == 65361)
		data->player.turn_direction = 0;
	return (0);
}

void	render_map(t_mlx *mlxstruct, t_cube *data)
{
	mlxstruct->mlx = mlx_init();
	init_textures(data);
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, WIDTH, HEIGHT, "cub3D");
	mlxstruct->img.img = mlx_new_image(mlxstruct->mlx, WIDTH, HEIGHT);
	mlxstruct->img.addr = mlx_get_data_addr(mlxstruct->img.img,
			&mlxstruct->img.bits_per_pixel,
			&mlxstruct->img.line_length,
			&mlxstruct->img.endian);
	mlx_hook(mlxstruct->win, 2, 1L << 0, handle_key_press, data);
	mlx_hook(mlxstruct->win, 17, 0, handle_close, data);
	mlx_hook(mlxstruct->win, 3, 1L << 1, handle_key_release, data);
	mlx_hook(mlxstruct->win, 6, 1L << 6, mouse_move, data);
	mlx_loop_hook(mlxstruct->mlx, rendering, data);
	mlx_loop(mlxstruct->mlx);
}
