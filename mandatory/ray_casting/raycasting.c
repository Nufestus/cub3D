/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:14:46 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 18:14:34 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
		{
			data->ray.perpwalldist = data->ray.sidedist_x
				- data->ray.deltadist_x;
		}
		else
		{
			data->ray.perpwalldist = data->ray.sidedist_y
				- data->ray.deltadist_y;
		}
		draw_line(x, data);
		x++;
	}
}
