/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_help_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:56:57 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/14 13:42:05 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	check(t_cube *data, int x, int y)
{
	int	ix;
	int	iy;

	ix = (int)x;
	iy = (int)y;
	if (iy < 0 || ix < 0)
		return (1);
	if (iy >= get_map_height(data->map))
		return (1);
	if (ix >= data->dimensions[iy])
		return (1);
	return (0);
}

int	is_wall(t_cube *data, double x, double y)
{
	if (check(data, x, y))
		return (1);
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

void	move_front(t_cube *data, double newX, double newY)
{
	newX = data->player.x + data->player.dir_x * data->player.speed;
	newY = data->player.y + data->player.dir_y * data->player.speed;
	if (!collides(data, newX, data->player.y)
		&& !collides(data, data->player.x, newY))
	{
		data->player.x = newX;
		data->player.y = newY;
	}
}

void	update_player(t_cube *data)
{
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	if (data->player.move_direction_front == 1)
		move_front(data, new_x, new_y);
	if (data->player.move_direction_front == -1)
		move_back(data, new_x, new_y);
	if (data->player.move_direction_side == 1)
		move_right(data, new_x, new_y);
	if (data->player.move_direction_side == -1)
		move_left(data, new_x, new_y);
	if (data->player.turn_direction == -1)
		rotate_left(data);
	if (data->player.turn_direction == 1)
		rotate_right(data);
}
