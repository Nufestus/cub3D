/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:55:36 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 17:40:52 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_back(t_cube *data, double *newX, double *newY)
{
	*newX = data->player.x - data->player.dir_x * PLR_SPEED;
	if (!collides(data, *newX, data->player.y))
		data->player.x = *newX;
	*newY = data->player.y - data->player.dir_y * PLR_SPEED;
	if (!collides(data, data->player.x, *newY))
		data->player.y = *newY;
}

void	move_right(t_cube *data, double *newX, double *newY)
{
	*newX = data->player.x + data->player.dir_y * PLR_SPEED;
	if (!collides(data, *newX, data->player.y))
		data->player.x = *newX;
	*newY = data->player.y - data->player.dir_x * PLR_SPEED;
	if (!collides(data, data->player.x, *newY))
		data->player.y = *newY;
}

void	move_left(t_cube *data, double *newX, double *newY)
{
	*newX = data->player.x - data->player.dir_y * PLR_SPEED;
	if (!collides(data, *newX, data->player.y))
		data->player.x = *newX;
	*newY = data->player.y + data->player.dir_x * PLR_SPEED;
	if (!collides(data, data->player.x, *newY))
		data->player.y = *newY;
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
