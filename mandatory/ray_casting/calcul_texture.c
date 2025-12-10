/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:36:07 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/09 17:50:47 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	get_wallx(t_cube *data)
{
	double	wall_x;

	if (data->ray.side == 0)
		wall_x = data->player.y + (data->ray.perpwalldist * data->ray.raydir_y);
	else
		wall_x = data->player.x + (data->ray.perpwalldist * data->ray.raydir_x);
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	get_tex_info(t_cube *data, t_img **tex, int *tex_x)
{
	double	wall_x;

	if (data->ray.side == 0)
	{
		if (data->ray.raydir_x > 0)
			*tex = &data->texture.wall_e;
		else
			*tex = &data->texture.wall_w;
	}
	else
	{
		if (data->ray.raydir_y > 0)
			*tex = &data->texture.wall_s;
		else
			*tex = &data->texture.wall_n;
	}
	wall_x = get_wallx(data);
	*tex_x = (int)(wall_x * (double)(*tex)->img_width);
}
