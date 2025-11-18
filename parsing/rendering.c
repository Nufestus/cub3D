/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:41:32 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/18 13:51:41 by aammisse         ###   ########.fr       */
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
                my_mlx_pixel_put(&data->mlxstruct, cx + x, cy + y, 0x00FF00);
            }
        }
    }
}

void draw_tile(t_cube *data, int color, int x, int y)
{
	int boundx;
	int boundy;
	int savex;

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

int rendering(t_cube *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_tile(data, 0xFFFFFF, j * TILE_SIZE, i * TILE_SIZE);
			else if (data->map[i][j] == '0')
				draw_tile(data, 0x000000, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	draw_filled_circle(data->pixelx, data->pixely, 3, data);
	// int k  = 0;
	// while (data->map[k])
	// {
	// 	int f = 0;
	// 	while (data->map[k][f])
	// 	{
	// 		if (plrx == f * TILE_SIZE && plry == k * TILE_SIZE)

	// 		f++;
	// 	}
	// 	k++;
	// }
	mlx_put_image_to_window(data->mlxstruct.mlx, data->mlxstruct.win, data->mlxstruct.img.img, 0, 0);
	return (0);
}

void render_map(t_mlx *mlxstruct, t_cube *data)
{
	mlxstruct->mlx = mlx_init();
	mlxstruct->win = mlx_new_window(mlxstruct->mlx, data->width * TILE_SIZE, data->height * TILE_SIZE, "cub3D");
	mlxstruct->img.img = mlx_new_image(mlxstruct->mlx, data->width * TILE_SIZE, data->height * TILE_SIZE);
	mlxstruct->img.addr = mlx_get_data_addr(mlxstruct->img.img, &mlxstruct->img.bits_per_pixel, &mlxstruct->img.line_length,
											&mlxstruct->img.endian);
	mlx_key_hook(mlxstruct->win, handle_keys, data);
	mlx_loop_hook(mlxstruct->mlx, rendering, data);
	mlx_loop(mlxstruct->mlx);
}