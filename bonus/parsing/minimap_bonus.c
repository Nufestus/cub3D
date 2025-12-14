/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:57:22 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/14 13:41:50 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_minimap_helper(t_minimap *mini, t_cube *data)
{
	if (data->map[(*mini).map_y][(*mini).map_x] == '1')
		draw_tile(data, 0x000000,
			(*mini).draw_x, (*mini).draw_y);
	else if (data->map[(*mini).map_y][(*mini).map_x] == 'D' &&
		is_door_closed(data, (*mini).map_x, (*mini).map_y))
		draw_tile(data, 0x0000FF, (*mini).draw_x, (*mini).draw_y);
	else if (data->map[(*mini).map_y][(*mini).map_x] == 'D' &&
		!is_door_closed(data, (*mini).map_x, (*mini).map_y))
		draw_tile(data, 0xFFFF, (*mini).draw_x, (*mini).draw_y);
	else
		draw_tile(data, 0xFFFFFF, (*mini).draw_x, (*mini).draw_y);
	if (is_player(data, (*mini).map_x, (*mini).map_y))
		draw_filled_circle((*mini).draw_x + TILE_SIZE / 2,
			(*mini).draw_y + TILE_SIZE / 2, 3, data);
}

void	init_mini(t_minimap *mini, t_cube *data)
{
	(*mini).map_x = (int)data->player.x + (*mini).dx;
	(*mini).map_y = (int)data->player.y + (*mini).dy;
	(*mini).draw_x = ((*mini).dx + 4) * TILE_SIZE;
	(*mini).draw_y = ((*mini).dy + 4) * TILE_SIZE;
}

void	draw_minimap(t_cube *data)
{
	t_minimap	mini;

	mini.map_h = 0;
	mini.map_w = get_longest_line(data->map, &mini.map_h);
	mini.dy = -4;
	while (mini.dy <= 4)
	{
		mini.dx = -4;
		while (mini.dx <= 4)
		{
			init_mini(&mini, data);
			if (mini.map_x < 0 || mini.map_y < 0 || mini.map_y >= mini.map_h
				|| mini.map_x >= (int)ft_strlen(data->map[mini.map_y]))
			{
				mini.dx++;
				draw_tile(data, 0x222222, mini.draw_x, mini.draw_y);
				continue ;
			}
			draw_minimap_helper(&mini, data);
			mini.dx++;
		}
		mini.dy++;
	}
}

int	is_player(t_cube *data, int x, int y)
{
	if (x == (int)data->player.x && y == (int)data->player.y)
		return (1);
	return (0);
}

size_t	get_longest_line(char **map, int *a)
{
	int		i;
	size_t	longest;

	i = 0;
	longest = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > longest)
			longest = ft_strlen(map[i]);
		i++;
	}
	*a = i;
	return (longest);
}
