/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 09:36:07 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/01 18:11:20 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

double	get_wallX(t_cube *data)
{
	double wallX;

	if (data->ray.side == 0)
		wallX = data->player.y + (data->ray.perpWallDist * data->ray.rayDirY);
	else
		wallX = data->player.x + (data->ray.perpWallDist * data->ray.rayDirX);
	wallX -= floor(wallX);
	return (wallX);
}

void	get_tex_info(t_cube *data, t_img **tex, int *tex_x)
{
	double wallX;

	if (data->ray.side == 0)
	{
		if (data->ray.rayDirX > 0)
			*tex = &data->texture.wall_E;
		else
			*tex = &data->texture.wall_W;
	}
	else
	{
		if (data->ray.rayDirY > 0)
			*tex = &data->texture.wall_S;
		else
			*tex = &data->texture.wall_N;
	}
	if (data->ray.door == 1)
		*tex = &data->texture.door;
	wallX = get_wallX(data);
	*tex_x = (int)(wallX * (double)(*tex)->img_width);
	// if ((data->ray.side == 0 && data->ray.rayDirX > 0)
	// 	|| (data->ray.side == 1 && data->ray.rayDirY < 0))
	// 	*tex_x = (*tex)->img_width - *tex_x - 1;
}