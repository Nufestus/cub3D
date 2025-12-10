/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:40:31 by aammisse          #+#    #+#             */
/*   Updated: 2025/12/09 15:14:02 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	openmap(t_cube *data)
{
	int	fd;

	fd = open(data->map_file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Unable to Open file!\n", 22);
		free(data->map_file);
		exit(1);
	}
	return (fd);
}

int	check_player(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (strchr("NSEW", map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count > 1 || !count)
		return (1);
	return (0);
}

int	parse_map(t_cube *data)
{
	if (check_newline(data->map))
		return (1);
	if (check_player(data->map))
		return (1);
	if (check_edges(data->map))
		return (1);
	if (check_middle(data->map, data))
		return (1);
	return (0);
}

void	create_map(t_cube *data)
{
	make_map(data);
	if (parse_map(data))
	{
		write(2, "Error\n", 7);
		free_all(data);
		exit(1);
	}
}
