/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:40:31 by aammisse          #+#    #+#             */
/*   Updated: 2025/11/18 13:54:19 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int openmap(char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Unable to Open file!\n", 22);
		exit(1);
	}
	return (fd);
}

int check_player(char **map)
{
	int i;
	int j;
	int count;

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

int parse_map(t_cube *data)
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

void create_map(t_cube *data)
{
	make_map(data);
	if (parse_map(data))
	{
		write(2, "Error\n", 7);
		exit(1);
	}
}