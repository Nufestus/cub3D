/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:56:57 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 17:39:42 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_wall(t_cube *data, double x, double y)
{
	if (data->map[(int)y][(int)x] == '1'
		|| (data->map[(int)y][(int)x] == 'D'
		&& is_door_closed(data, x, y)))
		return (1);
	return (0);
}

int	collides(t_cube *data, double x, double y)
{
	double	r;

	r = HITBOX;
	if (is_wall(data, x + r, y))
		return (1);
	if (is_wall(data, x - r, y))
		return (1);
	if (is_wall(data, x, y + r))
		return (1);
	if (is_wall(data, x, y - r))
		return (1);
	if (is_wall(data, x - r, y - r))
		return (1);
	if (is_wall(data, x + r, y + r))
		return (1);
	if (is_wall(data, x + r, y - r))
		return (1);
	if (is_wall(data, x - r, y + r))
		return (1);
	return (0);
}

void	move_front(t_cube *data, double *newX, double *newY)
{
	*newX = data->player.x + data->player.dir_x * PLR_SPEED;
	if (!collides(data, *newX, data->player.y))
		data->player.x = *newX;
	*newY = data->player.y + data->player.dir_y * PLR_SPEED;
	if (!collides(data, data->player.x, *newY))
		data->player.y = *newY;
}

void	update_player(t_cube *data)
{
	double	new_x;
	double	new_y;

	if (data->player.move_direction_front == 1)
		move_front(data, &new_x, &new_y);
	if (data->player.move_direction_front == -1)
		move_back(data, &new_x, &new_y);
	if (data->player.move_direction_side == 1)
		move_right(data, &new_x, &new_y);
	if (data->player.move_direction_side == -1)
		move_left(data, &new_x, &new_y);
	if (data->player.turn_direction == -1)
		rotate_left(data);
	if (data->player.turn_direction == 1)
		rotate_right(data);
}

int	create_rgb(t_colors *color)
{
	return ((color->r << 16) | (color->g << 8) | (color->b));
}
