/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:25:52 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/01 12:14:43 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void load_textures(t_cube *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlxstruct.mlx, path, &img->img_width, &img->img_height);
	if (!img->img)
    {
        printf("Error\nTexture loading failed for path: |%s|\n", path);
        // Clean exit or return
        exit(1); 
    }
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

void init_textures(t_cube *data)
{
	load_textures(data, &data->texture.floor, "./textures/floor.xpm");
	load_textures(data, &data->texture.sky, "./textures/sky.xpm");
	load_textures(data, &data->texture.wall_N, data->texture.north);
	load_textures(data, &data->texture.wall_S, data->texture.south);
	load_textures(data, &data->texture.wall_W, data->texture.west);
	load_textures(data, &data->texture.wall_E, data->texture.east);
}

unsigned int get_pixel_color(t_img *img, int x, int y)
{
	char *pixel;

	if (x < 0 || x >= img->img_width || y < 0 || y >= img->img_height)
		return (0);

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	
	return (*(unsigned int *)pixel);
}