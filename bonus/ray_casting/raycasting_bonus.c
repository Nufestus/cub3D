/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:14:46 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 13:42:10 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	set_darkness(t_cube *data, int *color)
{
	t_colors	rgb;
	double		darkness_factor;

	if (data->dark == 1)
	{
		darkness_factor = exp(-data->ray.perpwalldist * 0.4);
		if (darkness_factor > 1.0)
			darkness_factor = 1.0;
		if (darkness_factor < 0.0)
			darkness_factor = 0.0;
		rgb.r = ((*color >> 16) & 0xFF) * darkness_factor;
		rgb.g = ((*color >> 8) & 0xFF) * darkness_factor;
		rgb.b = (*color & 0xFF) * darkness_factor;
		*color = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
	}
}

void	cast_rays(t_cube *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		initialize_values(x, data);
		calculate_step(data);
		dda(data);
		if (data->ray.side == 0)
			data->ray.perpwalldist = data->ray.sidedist_x
				- data->ray.deltadist_x;
		else
			data->ray.perpwalldist = data->ray.sidedist_y
				- data->ray.deltadist_y;
		draw_line(x, data);
		x++;
	}
}

int	is_door_closed(t_cube *data, double x, double y)
{
	t_door	*door;

	door = get_units(data, (int)x, (int)y);
	if (door->open == 0)
		return (1);
	return (0);
}

int	is_closed(t_cube *data)
{
	t_door	*door;

	door = get_units(data, data->ray.map_x, data->ray.map_y);
	if (door->open == 0)
		return (1);
	return (0);
}

void	draw_pixel(t_cube *data, t_sprite *sprite)
{
	unsigned int	color;

	color = get_pixel_color(sprite->image, sprite->x, sprite->y);
	if (color != 0xFF000000 && color != 0x0)
	{
		if (sprite->start + sprite->x >= 0 && sprite->start + sprite->x < WIDTH
			&& sprite->end + sprite->y >= 0 && sprite->end + sprite->y < HEIGHT)
			my_mlx_pixel_put(&data->mlxstruct, sprite->start + sprite->x,
				sprite->end + sprite->y, color);
	}
}
