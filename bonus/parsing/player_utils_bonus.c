/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:02:54 by mouerchi          #+#    #+#             */
/*   Updated: 2025/12/14 13:41:53 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	set_player_north(t_cube *data)
{
	data->player.dir_x = 0;
	data->player.dir_y = -1;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0;
}

static void	set_player_south(t_cube *data)
{
	data->player.dir_x = 0;
	data->player.dir_y = 1;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0;
}

static void	set_player_east(t_cube *data)
{
	data->player.dir_x = 1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
}

static void	set_player_west(t_cube *data)
{
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = -0.66;
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
