/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:41:32 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/10 15:21:05 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	rendering(t_cube *data)
{
	update_player(data);
	cast_rays(data);
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
	get_map_dimensions(data);
	mlxstruct->mlx = mlx_init();
	init_textures(data);
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, WIDTH, HEIGHT, "cub3D");
	mlxstruct->img.img = mlx_new_image(mlxstruct->mlx, WIDTH, HEIGHT);
	mlxstruct->img.addr = mlx_get_data_addr(mlxstruct->img.img,
			&mlxstruct->img.bits_per_pixel,
			&mlxstruct->img.line_length,
			&mlxstruct->img.endian);
	mlx_hook(mlxstruct->win, 2, 1L << 0, handle_key_press, data);
	mlx_hook(mlxstruct->win, 3, 1L << 1, handle_key_release, data);
	mlx_hook(mlxstruct->win, 17, 0, handle_close, data);
	mlx_loop_hook(mlxstruct->mlx, rendering, data);
	mlx_loop(mlxstruct->mlx);
}
