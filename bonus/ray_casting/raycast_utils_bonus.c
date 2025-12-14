/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:55:36 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 13:42:07 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	move_back(t_cube *data, double newX, double newY)
{
	newX = data->player.x - data->player.dir_x * data->player.speed;
	newY = data->player.y - data->player.dir_y * data->player.speed;
	if (!collides(data, newX, data->player.y)
		&& !collides(data, data->player.x, newY))
	{
		data->player.x = newX;
		data->player.y = newY;
	}
}

void	move_right(t_cube *data, double newX, double newY)
{
	newX = data->player.x + data->player.dir_y * data->player.speed;
	newY = data->player.y - data->player.dir_x * data->player.speed;
	if (!collides(data, newX, data->player.y)
		&& !collides(data, data->player.x, newY))
	{
		data->player.x = newX;
		data->player.y = newY;
	}
}

void	move_left(t_cube *data, double newX, double newY)
{
	newX = data->player.x - data->player.dir_y * data->player.speed;
	newY = data->player.y + data->player.dir_x * data->player.speed;
	if (!collides(data, newX, data->player.y)
		&& !collides(data, data->player.x, newY))
	{
		data->player.x = newX;
		data->player.y = newY;
	}
}

void	rotate_left(t_cube *data)
{
	double	rot;
	double	olddir_x;
	double	oldplane_x;

	rot = -PLR_ROTATE;
	olddir_x = data->player.dir_x;
	oldplane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(rot)
		- data->player.dir_y * sin(rot);
	data->player.dir_y = olddir_x * sin(rot)
		+ data->player.dir_y * cos(rot);
	data->player.plane_x = data->player.plane_x * cos(rot)
		- data->player.plane_y * sin(rot);
	data->player.plane_y = oldplane_x * sin(rot)
		+ data->player.plane_y * cos(rot);
}

void	rotate_right(t_cube *data)
{
	double	rot;
	double	olddir_x;
	double	oldplane_x;

	rot = PLR_ROTATE;
	olddir_x = data->player.dir_x;
	oldplane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(rot)
		- data->player.dir_y * sin(rot);
	data->player.dir_y = olddir_x * sin(rot)
		+ data->player.dir_y * cos(rot);
	data->player.plane_x = data->player.plane_x * cos(rot)
		- data->player.plane_y * sin(rot);
	data->player.plane_y = oldplane_x * sin(rot)
		+ data->player.plane_y * cos(rot);
}
