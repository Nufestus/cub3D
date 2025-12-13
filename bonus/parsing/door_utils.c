/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:54:27 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/09 16:39:48 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	safe_close_door(t_cube *data, t_door *door)
{
	if (door->open == 0)
		return ;
	door->open = 0;
	if (collides(data, data->player.x, data->player.y))
	{
		door->open = 1;
		return ;
	}
}

void	open_close_door(t_cube *data)
{
	t_door	*door;
	int		x;
	int		y;

	x = 0;
	y = 0;
	door = get_door_coordinates(data, x, y);
	if (!door)
		destroy_all(data);
	if (door->open)
		safe_close_door(data, door);
	else
		door->open = 1;
}

int	is_next_door(t_cube *data)
{
	if (data->map[(int)data->player.y + 1][(int)data->player.x] == 'D'
		|| data->map[(int)data->player.y - 1][(int)data->player.x] == 'D'
		|| data->map[(int)data->player.y][(int)data->player.x + 1] == 'D'
		|| data->map[(int)data->player.y][(int)data->player.x - 1] == 'D')
		return (1);
	return (0);
}

t_door	*get_door_coordinates(t_cube *data, int x, int y)
{
	if (data->map[(int)data->player.y + 1][(int)data->player.x] == 'D')
	{
		x = (int)data->player.x;
		y = (int)data->player.y + 1;
	}
	else if (data->map[(int)data->player.y - 1][(int)data->player.x] == 'D')
	{
		x = (int)data->player.x;
		y = (int)data->player.y - 1;
	}
	else if (data->map[(int)data->player.y][(int)data->player.x + 1] == 'D')
	{
		x = (int)data->player.x + 1;
		y = (int)data->player.y;
	}
	else if (data->map[(int)data->player.y][(int)data->player.x - 1] == 'D')
	{
		x = (int)data->player.x - 1;
		y = (int)data->player.y;
	}
	return (get_units(data, x, y));
}

t_door	*get_units(t_cube *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->doors[i].count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&(data->doors[i]));
		i++;
	}
	return (NULL);
}
