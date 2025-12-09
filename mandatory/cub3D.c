/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:58:26 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 12:48:33 by mouerchi         ###   ########.fr       */
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


void	initialize_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->img_width = 0;
	img->img_height = 0;
}

void initialize_texture(t_cube *data)
{
	data->texture.north = NULL;
	data->texture.south = NULL;
	data->texture.east = NULL;
	data->texture.west = NULL;
	initialize_img(&data->texture.wall_N);
	initialize_img(&data->texture.wall_S);
	initialize_img(&data->texture.wall_E);
	initialize_img(&data->texture.wall_W);
	initialize_img(&data->texture.floor);
	initialize_img(&data->texture.sky);
}

void initialize_all(t_cube *data, char *file)
{
	data->map_file = NULL;
	data->map = NULL;
	data->list_map = NULL;
	data->map_fd = -1;
	data->mlxstruct.mlx = NULL;
	data->mlxstruct.win = NULL;
	data->map_file = ft_strdup(file);
	data->map_fd = openmap(data);
	initialize_img(&data->mlxstruct.img);
	initialize_player(data);
	initialize_texture(data);
}

int	main(int ac, char **av)
{
	t_cube	data;

	if (ac != 2)
	{
		write(2, "Invalid File Map!\n", 19);
		return (1);
	}
	initialize_all(&data, av[1]);
	read_from_map(&data);
	create_map(&data);
	render_map(&data.mlxstruct, &data);
}
