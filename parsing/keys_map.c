/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:42:16 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/22 16:28:50 by aammisse         ###   ########.fr       */
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
