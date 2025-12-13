/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:58:26 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/12 12:25:05 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_player(t_cube *data)
{
	data->player.x = 0;
	data->player.y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
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

void	initialize_texture(t_cube *data)
{
	int	i;

	data->texture.north = NULL;
	data->texture.south = NULL;
	data->texture.east = NULL;
	data->texture.west = NULL;
	initialize_img(&data->texture.wall_n);
	initialize_img(&data->texture.wall_s);
	initialize_img(&data->texture.wall_e);
	initialize_img(&data->texture.wall_w);
	initialize_img(&data->texture.floor);
	initialize_img(&data->texture.door);
	i = 0;
	while (i < 8)
	{
		initialize_img(&data->texture.sprite.torch[i]);
		i++;
	}
}

void	initialize_all(t_cube *data, char *file)
{
	data->anime = 0;
	data->dark = 0;
	data->mouse_x = 0;
	data->map_file = NULL;
	data->map = NULL;
	data->list_map = NULL;
	data->map_fd = -1;
	data->mlxstruct.mlx = NULL;
	data->mlxstruct.win = NULL;
	data->doors = NULL;
	data->dimensions = NULL;
	data->map_file = ft_strdup(file);
	data->map_fd = openmap(data);
	data->player.speed = 0.07;
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
	create_doors(&data);
	render_map(&data.mlxstruct, &data);
}
