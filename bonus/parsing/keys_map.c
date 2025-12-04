/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:42:16 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/03 19:49:12 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void my_mlx_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char *dst;

	dst = NULL;
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int calculate_pixel(int fract)
{
	return (fract * TILE_SIZE);
}

int	mouse_move(int x, int y, t_cube *data)
{
	(void)y;
	int mid;

	mid = WIDTH / 4;
	if(x > mid * 3)
		data->player.turn_direction = 1;
	else if (x < mid)
		data->player.turn_direction = -1;
	else
		data->player.turn_direction = 0;
	return (0);
}
