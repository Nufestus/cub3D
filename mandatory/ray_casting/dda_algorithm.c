/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:57:36 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/13 14:23:45 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	initialize_values(int x, t_cube *data)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	data->ray.raydir_x = data->player.dir_x + data->player.plane_x * camera_x;
	data->ray.raydir_y = data->player.dir_y + data->player.plane_y * camera_x;
	data->ray.map_x = (int)data->player.x;
	data->ray.map_y = (int)data->player.y;
	data->ray.deltadist_x = fabs(1 / data->ray.raydir_x);
	data->ray.deltadist_y = fabs(1 / data->ray.raydir_y);
	data->ray.hit = 0;
}

void	calculate_step(t_cube *data)
{
	if (data->ray.raydir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.sidedist_x = (data->player.x - data->ray.map_x)
			* data->ray.deltadist_x;
	}
	else if (data->ray.raydir_x > 0)
	{
		data->ray.step_x = 1;
		data->ray.sidedist_x = (data->ray.map_x + 1.0 - data->player.x)
			* data->ray.deltadist_x;
	}
	if (data->ray.raydir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.sidedist_y = (data->player.y - data->ray.map_y)
			* data->ray.deltadist_y;
	}
	else if (data->ray.raydir_y > 0)
	{
		data->ray.step_y = 1;
		data->ray.sidedist_y = (data->ray.map_y + 1.0 - data->player.y)
			* data->ray.deltadist_y;
	}
}

void	dda(t_cube *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedist_x < data->ray.sidedist_y)
		{
			data->ray.map_x += data->ray.step_x;
			data->ray.sidedist_x += data->ray.deltadist_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.map_y += data->ray.step_y;
			data->ray.sidedist_y += data->ray.deltadist_y;
			data->ray.side = 1;
		}
		if (is_wall(data, data->ray.map_x, data->ray.map_y))
			data->ray.hit = 1;
	}
}

void	set_resources(t_dda *dda, t_cube *data, int x)
{
	dda->lineheight = HEIGHT / data->ray.perpwalldist;
	dda->step = ((double)dda->tex->img_height / (double)dda->lineheight);
	dda->drawstart = -dda->lineheight / 2 + HEIGHT / 2;
	if (dda->drawstart < 0)
		dda->drawstart = 0;
	dda->drawend = dda->lineheight / 2 + HEIGHT / 2;
	if (dda->drawend >= HEIGHT)
		dda->drawend = HEIGHT - 1;
	dda->tex_pos = (dda->drawstart - HEIGHT / 2 + dda->lineheight / 2)
		* dda->step;
	dda->y = 0;
	while (dda->y < dda->drawstart)
	{
		my_mlx_pixel_put(&data->mlxstruct, x, dda->y,
			create_rgb(&data->texture.sky_color));
		dda->y++;
	}
	dda->y = dda->drawstart;
}

void	draw_line(int x, t_cube *data)
{
	t_dda	dda;

	get_tex_info(data, &dda.tex, &dda.tex_x);
	set_resources(&dda, data, x);
	while (dda.y < dda.drawend)
	{
		dda.tex_y = (int)dda.tex_pos % dda.tex->img_height;
		dda.tex_pos += dda.step;
		dda.color = get_pixel_color(dda.tex, dda.tex_x, dda.tex_y);
		my_mlx_pixel_put(&data->mlxstruct, x, dda.y, dda.color);
		dda.y++;
	}
	dda.y = dda.drawend;
	while (dda.y < HEIGHT)
	{
		my_mlx_pixel_put(&data->mlxstruct, x, dda.y,
			create_rgb(&data->texture.floor_color));
		dda.y++;
	}
}
