/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:42:16 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 16:27:18 by mouerchi         ###   ########.fr       */
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

int	mouse_move(int x, int y, t_cube *data)
{
	int	mid;

	(void)y;
	mid = WIDTH / 4;
	if (x > mid * 3)
		data->player.turn_direction = 1;
	else if (x < mid)
		data->player.turn_direction = -1;
	else
		data->player.turn_direction = 0;
	return (0);
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

void	draw_tile(t_cube *data, int color, int x, int y)
{
	int	boundx;
	int	boundy;
	int	savex;

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
