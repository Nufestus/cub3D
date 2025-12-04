/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:58:26 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/03 19:33:48 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void initialize_player(t_cube *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.dirX = 0;
	data->player.dirY = 0;
	data->player.planeX = 0;
	data->player.planeY = 0;
    data->player.move_direction_front = 0;
    data->player.move_direction_side = 0;
    data->player.turn_direction = 0;
}

void initialize_all(t_cube *data)
{
	initialize_player(data);
	data->anime = 0;
	data->mouse_x = 0;
	// everything else
}

int	main(int ac, char **av)
{
	t_cube	data;

	if (ac != 2)
	{
		write(2, "Invalid File Map!\n", 19);
		return (1);
	}
	initialize_all(&data);
	data.map_file = ft_strdup(av[1]);
	data.map_fd = openmap(av[1]);
	data.list_map = NULL;
	data.map = NULL;
	read_from_map(&data);
	create_map(&data);
	create_doors(&data);
	// printmap(&data);
	render_map(&data.mlxstruct, &data);
}
