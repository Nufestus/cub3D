/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:02:54 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/09 13:45:49 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	set_player_north(t_cube *data)
{
	data->player.dirX = 0;
	data->player.dirY = -1;
	data->player.planeX = 0.66;
	data->player.planeY = 0;
}

static void	set_player_south(t_cube *data)
{
	data->player.dirX = 0;
	data->player.dirY = 1;
	data->player.planeX = -0.66;
	data->player.planeY = 0;
}

static void	set_player_east(t_cube *data)
{
	data->player.dirX = 1;
	data->player.dirY = 0;
	data->player.planeX = 0;
	data->player.planeY = 0.66;
}

static void	set_player_west(t_cube *data)
{
	data->player.dirX = -1;
	data->player.dirY = 0;
	data->player.planeX = 0;
	data->player.planeY = -0.66;
}

void	set_player(t_cube *data, int i, int j, char **map)
{
	data->pixely = calculate_pixel(i) + (TILE_SIZE / 2);
	data->pixelx = calculate_pixel(j) + (TILE_SIZE / 2);
	data->player.x = data->pixelx / (double)TILE_SIZE;
	data->player.y = data->pixely / (double)TILE_SIZE;
	if (map[i][j] == 'N')
		set_player_north(data);
	else if (map[i][j] == 'S')
		set_player_south(data);
	else if (map[i][j] == 'E')
		set_player_east(data);
	else if (map[i][j] == 'W')
		set_player_west(data);
	map[i][j] = '0';
}
