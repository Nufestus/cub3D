/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:42:16 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/18 13:52:46 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

unsigned int get_pixel_address(t_mlx *mlx, int x, int y, t_cube *data)
{
	char *dst;

	dst = NULL;
	printf("%d - %d - %d - %d\n", x, y, data->width * TILE_SIZE, data->height * TILE_SIZE);
	if (x < 0 || y < 0 || x >= data->width * TILE_SIZE || y >= data->height * TILE_SIZE)
		return (INT_MAX);
	dst = mlx->img.addr + (y * mlx->img.line_length + x * (mlx->img.bits_per_pixel / 8));
	if (*(unsigned int *)dst == 0xFFFFFF)	
		return (1);
	return (0);
}

int handle_keys(int key, t_cube *data)
{
	if (key == ESC)
		exit(1);
	else if (key == W_KEY && get_pixel_address(&data->mlxstruct, data->pixelx, data->pixely - PLR_SPEED, data) != 1)
		data->pixely -= PLR_SPEED;
	else if (key == S_KEY && get_pixel_address(&data->mlxstruct, data->pixelx, data->pixely + PLR_SPEED, data) != 1)
		data->pixely += PLR_SPEED;
	else if (key == D_KEY && get_pixel_address(&data->mlxstruct, data->pixelx + PLR_SPEED, data->pixely, data) != 1)
		data->pixelx += PLR_SPEED;
	else if (key == A_KEY && get_pixel_address(&data->mlxstruct, data->pixelx - PLR_SPEED, data->pixely, data) != 1)
		data->pixelx -= PLR_SPEED;
	return (0);
}

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
