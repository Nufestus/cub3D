/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:42:16 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 13:58:59 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	dst = NULL;
	dst = mlx->img.addr + (y * mlx->img.line_length + x
			* (mlx->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	calculate_pixel(int fract)
{
	return (fract * TILE_SIZE);
}

void	draw_filled_circle(int cx, int cy, int radius, t_cube *data)
{
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				my_mlx_pixel_put(&data->mlxstruct, cx + x, cy + y, 0xFF0000);
			}
			x++;
		}
		y++;
	}
}

void	safe_destroy(void *mlx, t_img *img)
{
	if (img->img)
		mlx_destroy_image(mlx, img->img);
}

void	destroy_all(t_cube *data)
{
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_N);
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_S);
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_E);
	safe_destroy(data->mlxstruct.mlx, &data->texture.wall_W);
	safe_destroy(data->mlxstruct.mlx, &data->texture.floor);
	safe_destroy(data->mlxstruct.mlx, &data->texture.sky);
	safe_destroy(data->mlxstruct.mlx, &data->mlxstruct.img);
	if (data->mlxstruct.win)
		mlx_destroy_window(data->mlxstruct.mlx, data->mlxstruct.win);
	if (data->mlxstruct.mlx)
		mlx_destroy_display(data->mlxstruct.mlx);
	free_all(data);
	free(data->mlxstruct.mlx);
	exit(0);
}
